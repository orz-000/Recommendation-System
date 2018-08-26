#Ex10 interface module
#ID: s1240148
#Name: Shigeki Kobayashi
#Date: 07/25/2018
import phase1_func
import phase2
import phase1_db
import os,sys
import re
import MySQLdb

connection = MySQLdb.connect(
    host = 'localhost', user = 'root', passwd = 'root', db = 'ex10', charset = 'utf8')
cursor = connection.cursor()
cursor.execute("use ex10")

if __name__ == "__main__":
    phase1_db.init_database_phase1()
    phase2.init_database_phase2()

while(True):
        print("1:create\n2:delete\n3:insert\n4:get\n5:recommend\n6:recommend_friend\n7:search\n")
        inp = input("What do you want me to do?\n")
#insert part
        if(inp == "3"):
            print("where do you want to insert?")
            print("1:insert into lib\n2:insert into relation\n3:insert into url\n4:insert into word\n5:insert into link\n6:insert into location\n")
            inp = input()
            if(inp == "1"):
                phase1_db.insert_lib()
                phase1_db.insert_map()
            elif(inp == "2"):
                phase1_db.insert_relation()
                phase1_db.insert_map_relation()
            elif(inp == "3"): phase2.insert_url()
            elif(inp == "4"): phase2.insert_word()
            elif(inp == "5"): phase2.insert_link()
            elif(inp == "6"): phase2.insert_location()
#create part
        elif(inp == "1"):
            print("where do you want to create?")
            print("1:create lib\n2:create relation\n3:create url\n4:create word\n5:create link\n6:create location\n")
            inp = input()
            if(inp == "1"): phase1_db.create_lib()
            elif(inp == "2"): phase1_db.create_relation()
            elif(inp == "3"): phase2.create_url()
            elif(inp == "4"): phase2.create_word()
            elif(inp == "5"): phase2.create_link()
            elif(inp == "6"): phase2.create_location()
        elif(inp == "2"):
#create part
            print("where do you want to delete?")
            print("1:delete lib\n2:delete relation\n3:delete url\n4:delete word\n5:delete link\n6\:delete location\n")
            inp = input()
            if(inp == "1"): phase1_db.delete_lib()
            elif(inp == "2"): phase1_db.delete_relation()
            elif(inp == "3"): phase2.delete_url()
            elif(inp == "4"): phase2.delete_word()
            elif(inp == "5"): phase2.delete_link()
            elif(inp == "6"): phase2.delete_location()
        elif(inp == "4"):
#get part
            print("what do you want to get?")
            print("1:get user\n2:get book\n")
            inp = input()
            if(inp == "1"): print(phase1_db.get_user())
            elif(inp == "2"): print(phase1_db.get_book())
#recommend part
        elif(inp == "5"):
            phase1_func.similarlity()
            reco = phase1_func.recommend()
            res = phase1_func.map_sort(reco)
            phase1_func.show(res)
#recommend with union find part
        elif(inp == "6"):
            phase1_func.uni_init(phase1_db.uni)
            phase1_func.similarlity_uni(phase1_db.uni)
            reco = phase1_func.recommend()
            res = phase1_func.map_sort(reco)
            phase1_func.show(res)
#search part
        elif(inp == "7"):
            phase2.calc()
        else:
            print("please correct command")
