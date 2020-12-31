#include<bits/stdc++.h>
#include"ticket.h"
#include"admin.h"
#include"user.h"
using namespace std;

void print(pair<vs,vector<vs> > p)    {
    for (auto s:p.first) cout<<s<<" "; cout<<endl;
    for (auto row:p.second) {
        for (auto col:row)
            cout<<col<<" ";
        cout<<endl;
    }
    cout<<endl;
}

void print(vector<int> v)    {
    for (auto x:v) cout<<x<<" "; cout<<endl;
}

int main()  {
    // cout<<strHash("xlh")<<endl;
    // cout<<strHash("xjc")<<endl;
    // cout<<strHash("xby")<<endl;
    // cout<<strHash("xjj")<<endl;
    // cout<<strHash("Zayin")<<endl;
    // cout<<strHash("Ziyin")<<endl;
    assert(adminLogin::signIn("xlh","xlh"));
    assert(adminLogin::signIn("xjj","xjj"));
    assert(adminLogin::signIn("xjc","xjc"));
    assert(adminLogin::signIn("xby","xby"));

    assert(userLogin::signIn("Zayin","Zayin"));
    assert(userLogin::signIn("Ziyin","Ziyin"));


    admin a("xlh","xlh");
    
    // print(a.getBooks());
    // print(a.getBookTickets(1));
    // print(a.getPassengers());
    // print(a.getTickets());
    // print(a.getUserBooks(1));
    // print(a.getUsers());
    // print(a.getVehicles());

    cout<<"------------------------------------------"<<endl;

    user u("Zayin","Zayin");
    print(u.getPassengers());

    
    cout<<"------------------------------------------"<<endl;

    dbClient dbc;
    print(a.getUserBooks(1));
    print(dbc.getTickets());

    if (!u.book(3,{1,2}))
        cout<<dbc.getMsg()<<endl;
    print(a.getUserBooks(1));
    print(dbc.getTickets());

    cout<<"------------------------------------------"<<endl;

    u.refund(2);
    
    print(a.getUserBooks(1));
    print(dbc.getTickets());

    
    cout<<"------------------------------------------"<<endl;

    u.addPassenger("441284200001027894","邹丹梅","NULL","NULL");
    print(a.getPassengers());


    cout<<"end."<<endl;
    // cout<<adminLogin::signIn("xjj","xlh")<<endl;
    return 0;
}