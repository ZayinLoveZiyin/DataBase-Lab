#pragma once
#include<WinSock2.h>
#include"mysql.h"
#include <windows.h>
#include<bits/stdc++.h>
#pragma comment (lib,"libmysql.lib")
using namespace std;

using vs=vector<string>;

class dbClient  {
    MYSQL mysql;
    pair<vs,vector<vs> > query(string)   ;
    int count(string)  ;
    bool execute(const string& cmd);

    static string flitter(string)   ;

    int getid(string)  ;
    vector<int> getids(string,int)  ;

    vector<int> getseat(int);
    
    double getprice(int);

public:

    dbClient() ;

    string getMsg();

    pair<vs,vector<vs> > getVehicles(string cond="true")   ;
    pair<vs,vector<vs> > getBooks(string cond="true")   ;
    pair<vs,vector<vs> > getUsers(string cond="true");
    pair<vs,vector<vs> > getPassengers(string cond="true");
    pair<vs,vector<vs> > getTickets(string cond="true");
    bool addVehicle(double v_price,string v_from,string v_to,string v_start_time,string v_end_time,int v_cap=40);
    bool updVehicle(int v_id,double v_price,string v_from,string v_to,string v_start_time,string v_end_time,int v_cap=40);

    bool addPassenger(int u_id,string p_idcard_no,string p_name,string p_addr,string p_phone)   ;
    bool updPassenger(int p_id,string p_idcard_no,string p_name,string p_addr,string p_phone)   ;

    bool addUser(string u_nickname,size_t u_pwdhash)   ;
    bool updUser(int u_id,string u_nickname,string u_pwdhash)   ;

    bool addBook(int u_id,int v_id,vector<int> p_ids)   ;

    vector<int> getUserBook(int u_id,int b_id)  ;

    bool delBook(int u_id,int b_id)   ;
    
    pair<vs,vector<vs> > getBookTickets(int b_id,string cond="true");
};

