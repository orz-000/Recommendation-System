#Ex10 module of manupulating database and phase1's data
#ID: s1240148
#Name: Shigeki Kobayashi
#Date: 07/25/2018
import phase1_func
import os,sys
import re
import MySQLdb

#conect database
connection = MySQLdb.connect(
    host = 'localhost', user = 'root', passwd = 'root', db = 'ex10', charset = 'utf8')
cursor = connection.cursor()
#create tables
def init_database_phase1():
    cursor.execute("use ex10")
    cursor.execute("""create table lib(
    rowid int unsigned not null auto_increment,
    user int,
    book int,
    eval double,
    primary key (rowid));"""
    )
    cursor.execute("""create table relation(
    rowid int unsigned not null auto_increment,
    s int,
    t int,
    primary key (rowid));"""
    )
def create_lib():
    cursor.execute("""create table lib(
    rowid int unsigned not null auto_increment,
    user int,
    book int,
    eval double,
    primary key (rowid));"""
    )
def create_relation():
    cursor.execute("""create table relation(
    rowid int unsigned not null auto_increment,
    s int,
    t int,
    primary key (rowid));"""
    )
def delete_lib():
    cursor.execute("drop table lib")
def delete_relation():
    cursor.execute("drop table relation")
def insert_lib():
    #insert into database
    data = input("please type lib's parameter ")
    data_list = re.split("\s|\n",data)
    n = int(data_list[0])
    m = int(data_list[1])
    global e
    e  = int(data_list[2])
    valk = []
    phase1_func.input_init(n,m)
    for i in range(e):
        data = input()
        data_list = re.split("\s|\n",data)
        data_list[0] = int(data_list[0])
        data_list[1] = int(data_list[1])
        data_list[2] = float(data_list[2])
        valk.append(data_list)
        if(len(valk[0]) >= 1000):
            cursor.executemany("insert into lib(user,book,eval) value(%s,%s,%s);",valk)
            valk = []
    cursor.executemany("insert into lib(user,book,eval) value(%s,%s,%s);",valk)
    valk = []

def insert_relation():
    r = int(input())
    valk = []
    for i in range(r):
        data = input()
        data_list = re.split("\s|\n",data)
        data_list[0] = int(data_list[0])
        data_list[1] = int(data_list[1])
        valk.append(data_list)
        if(len(valk) >= 1000):
            cursor.executemany("insert into relation(s,t) value(%s,%s);",valk)
            valk = []
    cursor.executemany("insert into relation(s,t) value(%s,%s);",valk)
    valk = []
#define various func
def get_user():
    cursor.execute("select distinct user from lib")
    user = cursor.fetchall()
    return user
def get_book():
    cursor.execute("select distinct book from lib")
    book = cursor.fetchall()
    return book
def insert_map():
    cursor.execute("select* from lib")
    table = cursor.fetchall()
    for i in table:
        phase1_func.input_phase1(i[1],i[2],i[3])
def insert_map_relation():
    cursor.execute("select* from relation")
    table = cursor.fetchall()
    global uni
    global scc
    uni = phase1_func.get_uni()
    scc = phase1_func.get_scc(e)
    for i in table:
        #input relation about union find and strong connected component
        uni = phase1_func.input_relation(i[1],i[2],uni)
        scc = phase1_func.input_graph(i[1],i[2],scc)
