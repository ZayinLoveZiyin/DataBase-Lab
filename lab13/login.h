#pragma once
#include<bits/stdc++.h>
using namespace std;

size_t strHash(string s)    {
    static hash<string> h;
    return h(s);
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
        if (!mysql_real_connect(&mysql, "localhost", "root", "123456", "dingbao", 3306, 0, 0))\
            throw "mysql connection failed.";\

    bool query(string table,string account,size_t& pwd)    {
        mysqlConnect;

        if (mysql_query(&mysql,string(
            "select pwd\
            from "+table+"\
            where account="+flitter(account)
        ).c_str())) 
            return 0;

        MYSQL_RES* res=mysql_store_result(&mysql);
        MYSQL_ROW row=mysql_fetch_row(res);
        pwd=atoull(row[0]);
        return 1;
    }

    bool insert(string table,string account,size_t pwd) {
        mysqlConnect;

        return mysql_query(&mysql,string(
            "insert into "+table+"\
                value("+flitter(account)+","+to_string(pwd)+");"
        ).c_str());
    }
}

namespace adminLogin {
    bool signIn(string account,string pwd)  {
        size_t h1=strHash(pwd),h2;
        bool flag=pwdClient::query("user",account,h2);
        return flag&&h1==h2;
    }
}

namespace userLogin {
    bool signIn(string account,string pwd)  {
        size_t h1=strHash(pwd),h2;
        bool flag=pwdClient::query("user",account,h2);
        return flag&&h1==h2;
    }
    bool signUp(string account,string pwd)  {
        size_t h;
        if (pwdClient::query("user",account,h))
            return 0;
        return pwdClient::insert("user",account,strHash(pwd));
    }
}