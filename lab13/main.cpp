#include<WinSock2.h>
#include"mysql.h"
#include <windows.h>
#include<bits/stdc++.h>
#include"ticket.h"
#pragma comment (lib,"libmysql.lib")

int main()  {
    dbClient dbc;
    auto qry=dbc.getBookTickets(2);
    for (auto title:qry.first) cout<<title<<" "; cout<<endl;
    for (auto row:qry.second) {
        for (string col:row)
            cout<<col<<" "; 
        cout<<endl;
    }

    
    auto v=dbc.getUserBook(1,2);
    for (int x:v) cout<<x<<" "; cout<<endl;
    cout<<"end"<<endl;

    return 0;
}