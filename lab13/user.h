#pragma once
#include<bits/stdc++.h>
#include"ticket.h"
#include"login.h"
using namespace std;

struct user  {
    const int u_id;
    dbClient dbc;
    user(string name="",string pwd=""):u_id(userLogin::signIn(name,pwd))   {
        if (!~u_id)
            throw "account not exist or wrong password.";
    }

    bool book(int v_id,vector<int> p_ids)    {
        return dbc.addBook(u_id,v_id,p_ids);
    }    
    bool addPassenger(string p_idcard_no,string p_name,string p_addr="NULL",string p_phone="NULL")    {
        return dbc.addPassenger(u_id,p_idcard_no,p_name,p_addr,p_phone);
    }
    bool updPassenger(int p_id,string p_idcard_no,string p_name,string p_addr,string p_phone)    {
        return dbc.updPassenger(p_id,p_idcard_no,p_name,p_addr,p_phone);
    }
    pair<vs,vector<vs> > getPassengers()    {
        return dbc.getPassengers("u_id="+to_string(u_id));
    }
    bool refund(int b_id)   {
        return dbc.delBook(u_id,b_id);
    }
};
