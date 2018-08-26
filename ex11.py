import phase1_func
import phase2
import phase1_db
import os,sys
import re
import MySQLdb

connection = MySQLdb.connect(
    host = 'localhost', user = 'root', passwd = 'root', db = 'ex11_9', charset = 'utf8')
cursor = connection.cursor()
cursor.execute("use ex11_9")

if __name__ == "__main__":
    phase1_db.init_database_phase1()
    phase2.init_database_phase2()

while(True):
        inp = input("What do you want me to do?\n")
        print("input = ",inp)
        if(inp == "insert into lib"):
            phase1_db.insert_lib()
            phase1_db.insert_map()
        elif(inp == "insert into relation"):
            phase1_db.insert_relation()
            phase1_db.insert_map_relation()
        elif(inp == "create lib"): phase1_db.create_lib()
        elif(inp == "create relation"): phase1_db.create_relation()
        elif(inp == "delete lib"): phase1_db.delete_lib()
        elif(inp == "delete relation"): phase1_db.delete_relation()
        elif(inp == "get user"): phase1_db.get_user()
        elif(inp == "get book"): phase1_db.get_book()
        elif(inp == "insert into url"): phase2.insert_url()
        elif(inp == "insert into word"): phase2.insert_word()
        elif(inp == "insert into link"): phase2.insert_link()
        elif(inp == "insert into location"): phase2.insert_location()
        elif(inp == "create url"): phase2.create_url()
        elif(inp == "create word"): phase2.create_word()
        elif(inp == "create link"): phase2.create_link()
        elif(inp == "create location"): phase2.create_location()
        elif(inp == "delete url"): phase2.delete_url()
        elif(inp == "delete word"): phase2.delete_word()
        elif(inp == "delete link"): phase2.delete_link()
        elif(inp == "delete location"): phase2.delete_location()

        elif(inp == "recommend"):
            phase1_func.similarlity()
            reco = phase1_func.recommend()
            res = phase1_func.map_sort(reco)
            phase1_func.show(res)
        elif(inp == "recommend_friend"):
            phase1_func.uni_init(phase1_db.uni)
            phase1_func.similarlity_uni(phase1_db.uni)
            reco = phase1_func.recommend()
            res = phase1_func.map_sort(reco)
            phase1_func.show(res)
        elif(inp == "recommend_most_friend"):
            phase1_func.similarlity_scc(phase1_db.scc)
            reco = phase1_func.recommend()
            res = phase1_func.map_sort(reco)
            phase1_func.show(res)
        elif(inp == "search"):
            phase2.calc()
        else:
            print("please correct command")
