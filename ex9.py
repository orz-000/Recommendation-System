#Ex9
#ID: s1240148
#Name: Shigeki Kobayashi
#Date: 07/25/2018

import os,sys
import re
import MySQLdb

connection = MySQLdb.connect(
    host = 'localhost', user = 'root', passwd = 'root', db = 'ex9', charset = 'utf8')
cursor = connection.cursor()

src = './source'
files = os.listdir(src)
score = {}
query_score = {}
score_nor = {}
query_score_nor = {}
books = {}
mp = {}
sum = {}
res = {}
db_mp = {}
fi_valk = []
con_valk = []
link = []
location = []

if __name__ == "__main__":
    #initialize database
    cursor.execute("use ex9")
    cursor.execute("""create table url(
    rowid int unsigned not null auto_increment,
    url varchar(100) unique,
    primary key (rowid));"""
    )
    cursor.execute("""create table word(
    rowid int unsigned not null auto_increment,
    word varchar(100) unique,
    primary key (rowid));"""
    )
    cursor.execute("""create table link(
    rowid int unsigned not null auto_increment,
    source int,
    target int,
    primary key (rowid));"""
    )
    cursor.execute("""create table location(
    rowid int unsigned not null auto_increment,
    wordid int,
    urlid int,
    primary key (rowid));"""
    )

    #insert into database
    for i in range(len(files)):
        fi_valk.append(files[i])
        if(len(fi_valk) >= 1000):
            cursor.executemany("insert ignore into url(url) values(%s)",fi_valk)
            fi_valk = [] #create list so that store input data before bulk insert
        path = "./source/" + files[i]
        f = open(path,"r")
        content = f.read()
        content_list = re.split("\s|\n",content)
        for j in range(len(content_list)):
            if(content_list[j].find(".html") == -1):
                con_valk.append(content_list[j])
                if(len(con_valk) >= 1000): #if datas are more 1000, execute bulk insert
                    cursor.executemany("insert ignore into word(word) value(%s);",con_valk)
                    con_valk = []
            else:
                fi_valk.append(content_list[j])
                if(len(fi_valk) >= 1000): #if datas are more 1000, execute bulk insert
                    cursor.executemany("insert ignore into url(url) values(%s);",fi_valk)
                    fi_valk = []
    # bulk insert remain data into database
    cursor.executemany("insert ignore into url(url) values(%s)",fi_valk)
    cursor.executemany("insert ignore into word(word) value(%s);",con_valk)
    fi_valk = con_valk = []
    #show
    cursor.execute("select* from url")
    result = cursor.fetchall()
    #print(result)
    cursor.execute("select* from word")
    result = cursor.fetchall()
    #print(result)

    for i in range(len(files)):
        path = "./source/" + files[i]
        f = open(path,"r")
        content = f.read()
        content_list = re.split("\s|\n",content)
        for j in range(len(content_list)):
            if(content_list[j].find(".html") == -1):
                cursor.execute("select rowid from url where url = %s;",[files[i]])
                result = cursor.fetchall()
                url_id = result[0][0]
                cursor.execute("select rowid from word where word = %s;",[content_list[j]])
                result = cursor.fetchall()
                word_id = result[0][0]
                location.append((url_id,word_id))
                if(len(location) >= 1000):
                    cursor.executemany("insert into location(urlid,wordid) values(%s,%s)",location)
                    location = []
            else:
                cursor.execute("select rowid from url where url = %s",[files[i]])
                result = cursor.fetchall()
                source_id = result[0][0]
                cursor.execute("select rowid from url where url = %s",[content_list[j]])
                result = cursor.fetchall()
                target_id = result[0][0]
                link.append((source_id,target_id))
                if(len(link) <= 1000):
                    cursor.executemany("insert into link(source,target) values(%s,%s)",link)
                    link = []
    cursor.executemany("insert into location(urlid,wordid) values(%s,%s)",location)
    cursor.executemany("insert into link(source,target) values(%s,%s)",link)
    location = link = []
    #show
    cursor.execute("select* from link")
    result = cursor.fetchall()
    #print(result)
    cursor.execute("select* from location")
    result = cursor.fetchall()
    #print(result)

    query = input()

    #initialization
    cursor.execute("select* from url")
    files = cursor.fetchall()
    for i in range(len(files)):
        score[files[i][1]] = 1.0
        if(query_score.get(files[i][1],None) == None): query_score[files[i][1]] = 0
        query_list = re.split("\s",query)

    #delete duplication
    for q in range(len(query_list)):
        for qq in range(q+1,len(query_list)):
            if(query_list[q] == query_list[qq]):
                del query_list[qq]

    #calculate query_score
    cursor.execute("select* from link")
    link = cursor.fetchall()
    for j in range(len(link)):
        cursor.execute("select url from url where rowid = %s",[link[j][1]])
        source_name = cursor.fetchall()
        cursor.execute("select url from url where rowid = %s",[link[j][2]])
        target_name = cursor.fetchall()
        score[target_name[0][0]] = 1.0
        if books.get(source_name[0][0],None) == None: books[source_name[0][0]] = 1
        else: books[source_name[0][0]] += 1
        for k in range(len(query_list)):
            key = target_name[0][0] + ',' + query_list[k]
            if(target_name[0][0] == query_list[k] and not mp.get(key,False)):
                query_score[source_name[0][0]] += 1
                mp[key] = True

    cursor.execute("select* from location")
    location = cursor.fetchall()
    for j in range(len(location)):
        cursor.execute("select url from url where rowid = %s",[location[j][2]])
        url_name = cursor.fetchall()
        cursor.execute("select word from word where rowid = %s",[location[j][1]])
        word_name = cursor.fetchall()
        for k in range(len(query_list)):
            key = word_name[0][0] + ',' + query_list[k]
            if(word_name[0][0] == query_list[k] and not mp.get(key,False)):
                query_score[url_name[0][0]] += 1
                mp[key] = True
        for k in mp.keys():
            mp[k] = False

    #calculate score
    for k in range(20):
        for i in range(len(files)):
            if(sum.get(files[i][1],None) == None): sum[files[i][1]] = 0
        for j in range(len(link)):
            cursor.execute("select url from url where rowid = %s",[link[j][1]])
            source_name = cursor.fetchall()
            cursor.execute("select url from url where rowid = %s",[link[j][2]])
            target_name = cursor.fetchall()
            if(sum.get(target_name[0][0],None) == None): sum[target_name[0][0]] = 0
            sum[target_name[0][0]] += score[source_name[0][0]] / books[source_name[0][0]]

        for i in range(len(files)):
            score[files[i][1]] = 0.15 + 0.85 * sum[files[i][1]]
            sum[files[i][1]] = 0

    #normalization
    for i in range(len(files)):
        score_nor[files[i][1]] = score[files[i][1]] / max(score.values())
        query_score_nor[files[i][1]] = query_score[files[i][1]] / max(query_score.values())
        res[files[i][1]] = score_nor[files[i][1]] + query_score_nor[files[i][1]]
    #print result
    print("word page score")
    for i in range(len(files)):
        print("{:.3}".format(query_score_nor[files[i][1]]),':',"{:.3}".format(score_nor[files[i][1]]),':',"{:.3}".format(res[files[i][1]]),':',files[i][1])
