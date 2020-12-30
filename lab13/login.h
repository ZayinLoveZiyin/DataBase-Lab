#pragma once
#include<bits/stdc++.h>
#include"ticket.h"
using namespace std;

size_t strHash(string s)    {
    size_t hash=0;  
    for (size_t ch:s)
        hash=hash*131+ch;
    return hash;  
}

size_t atoull(string s) {
    stringstream ss(s);
    size_t t;
    ss>>t;
    return t;
}

namespace pwdClient  {
    static string flitter(string s)    {
        string t;
        for (char c:s)  {
            if (c=='\''||c=='\"')
                t.push_back('\\');
            t.push_back(c);
        }
        return "\'"+t+"\'";
    }

    #define mysqlConnect \
        MYSQL mysql;\
        mysql_init(&mysql);\
        if (!mysql_real_connect(&mysql, "localhost", "root", "123456", "ticket", 3306, 0, 0))\
            throw "mysql connection failed.";\

    int query(string table,string account,string cond="true")    {
        mysqlConnect;

        if (mysql_query(&mysql,string(
            "select "+table.substr(0,1)+"_id\
            from "+table+"\
            where "+table.substr(0,1)+"_nickname="+flitter(account)+"\
            and "+cond
        ).c_str()))  { 
            cerr<<"ERROR:"<<mysql_error(&mysql)<<endl;
            return 0;
        }

        MYSQL_RES* res=mysql_store_result(&mysql);
        MYSQL_ROW row=mysql_fetch_row(res);
        if (!row) return -1;
        return atoi(row[0]);
    }
}

namespace adminLogin {
    int signIn(string account,string pwd)  {
        return pwdClient::query("admin",account,"a_pwdhash="+to_string(strHash(pwd)));
    }
}

namespace userLogin {
    int signIn(string account,string pwd)  {        
        return pwdClient::query("user",account,"u_pwdhash="+to_string(strHash(pwd)));
    }
    bool signUp(string account,string pwd)  {
        if (~pwdClient::query("user",account))
            return 0;
        dbClient dbc;
        return dbc.addUser(account,strHash(pwd));
    }
}