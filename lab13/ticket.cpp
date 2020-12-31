#include"ticket.h"

using vs=vector<string>;

pair<vs,vector<vs> > dbClient::query(string cmd)    {
    vector<vs> rows;
    if (mysql_query(&mysql,cmd.c_str()))    {
        cerr<<"ERROR:"<<getMsg()<<endl;
        return make_pair(vs{},rows);
    }

    MYSQL_RES* res=mysql_store_result(&mysql);
    int col=mysql_num_fields(res);

    MYSQL_FIELD* fd=mysql_fetch_fields(res);

    vs title;
    for (int i=0;i<col;++i)
        title.push_back(fd[i].name);
        
    MYSQL_ROW row;
    while (row=mysql_fetch_row(res))    {
        rows.push_back({});
        for (int i=0;i<col;++i)
            if (row[i])
                rows.back().push_back(row[i]);
            else
                rows.back().push_back("NULL");
    }
    return make_pair(title,rows);
}

int dbClient::count(string cmd)   {
    auto q=query(cmd);
    return q.second.size();
}
bool dbClient::execute(const string& cmd) {
    if (mysql_query(&mysql, cmd.c_str())) 
        return 0;
    return 1;
}

string dbClient::flitter(string s)    {
    if (s=="NULL") return s;
    string t;
    for (char c:s)  {
        if (c=='\''||c=='\"')
            t.push_back('\\');
        t.push_back(c);
    }
    return "\'"+t+"\'";
}

int dbClient::getid(string cmd)   {
    vector<int> id;
    for (auto row:query(cmd).second)  {
        assert(row.size()==1);
        id.push_back(stoi(row.back()));
    }
    sort(id.begin(),id.end());
    for (int i=0;;++i)
        if (i>id.size()||id[i]!=i)
            return i;
}

vector<int> dbClient::getids(string cmd,int num=1)   {
    vector<int> id;
    for (auto row:query(cmd).second)  {
        assert(row.size()==1);
        id.push_back(stoi(row.back()));
    }
    sort(id.begin(),id.end());
    vector<int> res;
    for (int i=0,j=0;num;++i)   {
        if (j<id.size()&&id[j]==i)
            ++j;
        else    {
            --num;
            res.push_back(i);
        }
    }
    return res;
}

vector<int> dbClient::getseat(int v_id) {
    int seatlim=atoi(query("select v_cap\
                        from vehicle\
                        where v_id="+to_string(v_id)).second.back().back().c_str());
    auto _occupy=query("select t_seat\
                        from ticket natural join vehicle\
                        where v_id="+to_string(v_id)).second;
    set<int> occupy;
    vector<int> left;
    for (auto s:_occupy)
        occupy.insert(atoi(s.back().c_str()));
    for (int i=1;i<=seatlim;++i)
        if (!occupy.count(i))
            left.push_back(i);
    return left;
}    

double dbClient::getprice(int v_id) {
    auto price=query("select v_price\
                    from vehicle\
                    where v_id="+to_string(v_id)).second;
    if (price.size()!=1) return 0;
    return atoi(price.back().back().c_str());
}

dbClient::dbClient()  {
    mysql_init(&mysql);
    if (!mysql_real_connect(&mysql, "localhost", "root", "123456", "ticket", 3306, 0, 0))
        throw "mysql connection failed.";
}

string dbClient::getMsg() {
    return mysql_error(&mysql);
}

pair<vs,vector<vs> > dbClient::getVehicles(string cond)    {
    return query("select v_from,v_to,v_start_time,v_end_time,v_cap,v_price\
                    from vehicle\
                    where "+cond);
}    
pair<vs,vector<vs> > dbClient::getBooks(string cond)    {
    return query("select u_nickname,b_id,count(*) as tot\
                    from book natural join ticket\
                    natural join passenger\
                    natural join user\
                    where "+cond+"\
                    group by b_id");
}
pair<vs,vector<vs> > dbClient::getUsers(string cond) {
    return query("select u_id,u_nickname\
                    from user\
                    where "+cond);
}
pair<vs,vector<vs> > dbClient::getPassengers(string cond) {
    return query("select p_id,p_name,p_idcard_no,p_addr,p_phone\
                    from passenger\
                    where "+cond);
}    
pair<vs,vector<vs> > dbClient::getTickets(string cond) {
    return query("select t_id,p_name,p_idcard_no,v_from,v_to,v_start_time,v_end_time,t_seat,v_price\
                    from ticket natural join vehicle\
                    natural join passenger\
                    where "+cond);
}
bool dbClient::addVehicle(double v_price,string v_from,string v_to,string v_start_time,string v_end_time,int v_cap) {
    int v_id=getid("select v_id from vehicle");
    return execute("insert into vehicle\
                    value("+to_string(v_id)+","+\
                            to_string(v_price)+","+\
                            flitter(v_from)+","+\
                            flitter(v_to)+","+\
                            flitter(v_start_time)+","+\
                            flitter(v_end_time)+","+\
                            to_string(v_cap)+");");
}
bool dbClient::updVehicle(int v_id,double v_price,string v_from,string v_to,string v_start_time,string v_end_time,int v_cap) {
    return execute("update vehicle\
                    set v_price="+to_string(v_price)+",\
                        v_from="+flitter(v_from)+",\
                        v_to="+flitter(v_to)+",\
                        v_start_time="+flitter(v_start_time)+",\
                        v_end_time="+flitter(v_end_time)+",\
                        v_cap="+to_string(v_cap)+",\
                    where v_id="+to_string(v_id)+";");
}

bool dbClient::addPassenger(int u_id,string p_idcard_no,string p_name,string p_addr,string p_phone)    {
    int p_id=getid("select v_id from vehicle");
    return execute("insert into passenger\
                    value("+to_string(p_id)+","+\
                            to_string(u_id)+","+\
                            flitter(p_idcard_no)+","+\
                            flitter(p_name)+","+\
                            flitter(p_addr)+","+\
                            flitter(p_phone)+");");
}
bool dbClient::updPassenger(int p_id,string p_idcard_no,string p_name,string p_addr,string p_phone)    {
    return execute("update passenger\
                    set p_idcard_no="+flitter(p_idcard_no)+",\
                        p_name="+flitter(p_name)+",\
                        p_addr="+flitter(p_addr)+",\
                        p_phone="+flitter(p_phone)+",\
                    where p_id="+to_string(p_id)+";");
}

bool dbClient::addUser(string u_nickname,size_t u_pwdhash)    {
    int u_id=getid("select u_id from user");
    return execute("insert into user\
                        value("+to_string(u_id)+","+\
                                flitter(u_nickname)+","+\
                                to_string(u_pwdhash)+");");
}
bool dbClient::updUser(int u_id,string u_nickname,string u_pwdhash)    {
    return execute("update user\
                    set u_nickname="+flitter(u_nickname)+",\
                        u_pwdhash="+u_pwdhash+",\
                    where u_id="+to_string(u_id)+";");
}

//u_id,b_id must be existed
//FIX ME:this function must be atomic
bool dbClient::addBook(int u_id,int v_id,vector<int> p_ids)    {
    auto seat=getseat(v_id);
    auto t_ids=getids("select t_id from ticket",p_ids.size());
    assert(t_ids.size()==p_ids.size());
    int b_id=getid("select b_id from book");
    string t_tuple,b_tuple;
    try {
        if (seat.size()<p_ids.size()) throw -1;
        seat.resize(p_ids.size());
        double price=getprice(v_id);
        for (int i=0;i<p_ids.size();++i)
            if (getTickets("p_id="+to_string(p_ids[i])+" and \
                            v_id="+to_string(v_id)
                            ).second.size())
                throw -2;
            else    {
                t_tuple+="("+to_string(v_id)+","+\
                                    to_string(p_ids[i])+","+\
                                    to_string(t_ids[i])+","+\
                                    to_string(price)+","+\
                                    to_string(seat[i])+"),";
                b_tuple+="("+to_string(t_ids[i])+","+\
                             to_string(b_id)+"),";
            }
    }
    catch (int code) {
        switch (code)   {
            case -1:
                cerr<<"no enough seats for "<<p_ids.size()<<" persons."<<endl;
                break;
            case -2:
                cerr<<"someone have booked this vehicle."<<endl;
                break;
            default:
                assert(0);
        }
        return 0;
    }
    
    t_tuple.back()=b_tuple.back()=';';
    if (!execute("insert into ticket value"+t_tuple))
        cerr<<getMsg()<<endl;
    if (!execute("insert into book value"+b_tuple))
        cerr<<getMsg()<<endl;
    return 1;
}

vector<int> dbClient::getUserBook(int u_id,int b_id)   {
    auto _t_ids=query("select t_id\
                    from book natural join ticket\
                    natural join passenger\
                    natural join user\
                    where u_id="+to_string(u_id)+" and \
                            b_id="+to_string(b_id)).second;

    vector<int> t_ids;
    for (auto t_id:_t_ids) {
        assert(t_id.size()==1);
        t_ids.push_back(atoi(t_id.back().c_str()));
    }
    return t_ids;
}

bool dbClient::delBook(int u_id,int b_id)    {
    auto t_ids=getUserBook(u_id,b_id);
    execute("delete from book\
                where b_id="+to_string(b_id)+";");
    for (int t_id:t_ids)
        execute("delete from ticket\
                    where t_id="+to_string(t_id)+";");
    return 1;
}

pair<vs,vector<vs> > dbClient::getBookTickets(int b_id,string cond) {
    return query("select p_name,p_idcard_no,v_from,v_to,v_start_time,v_end_time,t_seat,v_price\
                    from book natural join ticket\
                    natural join vehicle\
                    natural join passenger\
                    where b_id="+to_string(b_id));
}

