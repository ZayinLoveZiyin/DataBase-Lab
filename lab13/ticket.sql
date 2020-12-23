drop database if exists Ticket;
create database Ticket;
use Ticket;

create table vehicle  ( 
    v_id int not null,
    v_price numeric(10,2) not null,
    v_from varchar(20) not null,
    v_to varchar(20) not null,
    v_start_time time not null,
    v_end_time time not null,
    v_cap int not null,
    primary key (v_id)
) ENGINE=InnoDB,charset=gbk;

insert into vehicle
    value   (1,850,'广州南','北京西','9:30','17:40',1000),
            (2,850,'北京西','广州南','9:30','17:40',1000);

select * from vehicle;

create table user  ( 
    u_id int not null,
    u_nickname varchar(20) unique not null,
    u_pwdhash varchar(20) not null,
    primary key (u_id)
) ENGINE=InnoDB,charset=gbk;

insert into user
    value   (1,'Zayin','sfgykgdbmndgj'),
            (2,'Ziyin','akjfgfkhajgsh');

select * from user;

create table passenger (
    p_id int not null,
    u_id int not null,
    p_idcard_no varchar(20) not null,
    p_name varchar(20) not null,
    p_addr varchar(20),
    p_phone varchar(20),
    primary key (p_id),
    foreign key (u_id) references user(u_id)
) ENGINE=InnoDB,charset=gbk;

insert into passenger
    value   (1,1,'441284200006021812','谢立辉',NULL,NULL),
            (2,1,'44128419991208342X','邱紫茵',NULL,NULL);

select * from passenger;

delimiter //
create trigger passenger_idcard_no before insert on passenger
for each row
begin
    if (length(new.p_idcard_no)!=18) then
        signal sqlstate '45000'
        set message_text = 'Insert Err : the p_idcard_no length is not 18';
    end if;
end//
delimiter ;

create table ticket  ( 
    v_id int not null,
    p_id int not null,
    t_id int not null,
    t_price numeric(10,2) not null,
    t_seat varchar(20),
    primary key (t_id),
    foreign key (v_id) references vehicle(v_id),
    foreign key (p_id) references passenger(p_id)
) ENGINE=InnoDB,charset=gbk;

insert into ticket
    value   (1,1,1,850,1),
            (1,2,2,850,2),
            (2,1,3,850,1),
            (2,2,4,850,2);

select * from ticket;

create table book (
    t_id int not null,
    b_id int not null,
    primary key (t_id),
    foreign key (t_id) references ticket(t_id)
) ENGINE=InnoDB,charset=gbk;

insert into book
    value   (1,1),
            (2,1),
            (3,2),
            (4,2);

select * from book;


create table admin  ( 
    a_id int not null,
    a_nickname varchar(20) unique not null,
    a_pwdhash varchar(20) not null,
    primary key (a_id)
) ENGINE=InnoDB,charset=gbk;

insert into admin
    value   (1,'xlh','adhakjaaasaad'),
            (2,'xjc','adhakjaaasaad'),
            (3,'xby','adhakjaaasaad'),
            (4,'xjj','adhakjaaasaad');

select * from admin;


