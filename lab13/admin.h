#pragma once
#include<bits/stdc++.h>
#include"ticket.h"
#include"login.h"
using namespace std;

struct admin  {
    dbClient dbc;
    admin(string name="",string pwd="")   {
        if (!adminLogin::signIn(name,pwd))
            throw "account not exist or wrong password.";
    }

    bool addVehicle(double v_price,string v_from,string v_to,string v_start_time,string v_end_time,int v_cap=40) {
        return dbc.addTicket(v_price,v_from,v_to,v_start_time,v_end_time,v_cap);
    }
    bool updVehicle(int v_id,double v_price,string v_from,string v_to,string v_start_time,string v_end_time,int v_cap=40) {
        return dbc.updVehicle(v_id,v_price,v_from,v_to,v_start_time,v_end_time,v_cap);
    }

    pair<vs,vector<vs> > getTickets() {
        return dbc.getTickets();
    }
    pair<vs,vector<vs> > getVehicles() {
        return dbc.getVehicles();
    }
    pair<vs,vector<vs> > getUsers() {
        return dbc.getUsers();
    }
    pair<vs,vector<vs> > getPassengers() {
        return dbc.getPassengers();
    }
    pair<vs,vector<vs> > getTickets() {
        return dbc.getTickets();
    }
    pair<vs,vector<vs> > getBooks() {
        return dbc.getBooks();
    }
    pair<vs,vector<vs> > getUserBooks(int u_id) {
        return dbc.getBooks("u_id="+to_string(u_id));
    }
    pair<vs,vector<vs> > getBookTickets(int b_id) {
        return dbc.getBookTickets("b_id="+to_string(b_id));
    }
};
