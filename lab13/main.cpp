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
    
    print(a.getBooks());
    print(a.getBookTickets(1));
    print(a.getPassengers());
    print(a.getTickets());
    print(a.getUserBooks(1));
    print(a.getUsers());
    print(a.getVehicles());

    cout<<"------------------------------------------"<<endl;

    print(a.getUserBooks(1));

    user u("Zayin","Zayin");
    u.refund(1);
    
    print(a.getUserBooks(1));
    // cout<<adminLogin::signIn("xjj","xlh")<<endl;
    return 0;
}