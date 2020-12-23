#pragma once
#include<bits/stdc++.h>
#include"ticket.h"
#include"login.h"
using namespace std;

struct user  {
    int u_id;
    dbClient dbc;
    user(string name="",string pwd=""):name(name)   {
        u_id=userLogin::signIn(name,pwd);
        if (!~u_id)
            throw "account not exist or wrong password.";
    }

    bool book(int v_id,vector<int> p_ids)    {
        return dbc.addBook(u_id,v_id,p_ids);
    }    
    bool addPassenger(string p_idcard_no,string p_name,string p_addr,string p_phone)    {
        return dbc.addBook(u_id,p_idcard_no,p_name,p_addr,p_phone);
    }
    bool updPassenger(int p_id,string p_idcard_no,string p_name,string p_addr,string p_phone)    {
        return dbc.addBook(p_id,p_idcard_no,p_name,p_addr,p_phone);
    }
    bool refund(int b_id)   {
        return dbc.delOrders(u_id,b_id);
    }
};
