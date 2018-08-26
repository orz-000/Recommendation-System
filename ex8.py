#Ex8
#ID: s1240148
#Name: Shigeki Kobayashi
#Date: 07/25/2018

import numpy as np
import os,sys
import re
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


if __name__ == "__main__":
    query = input()
#initialization
    for i in range(len(files)):
        #create score and query_score
        score[files[i]] = 1.0
        if(query_score.get(files[i],None) == None): query_score[files[i]] = 0
        query_list = re.split("\s",query)


        #delete duplication
        for q in range(len(query_list)):
            for qq in range(q+1,len(query_list)):
                if(query_list[q] == query_list[qq]):
                    del query_list[qq]

        path = "./source/" + files[i]
        f = open(path,"r")
        content = f.read()
        content_list = re.split("\s|\n",content)

        #initialization book and caluculate query_score
        for j in range(len(content_list)):
            if(content_list[j].find(".html") != -1):
                score[content_list[j]] = 1.0
                if books.get(files[i],None) == None: books[files[i]] = 1
                else: books[files[i]] += 1

            for k in range(len(query_list)):
                key = content_list[j]
                if(content_list[j] == query_list[k] and not mp.get(key,False)):
                    query_score[files[i]] += 1
                    mp[key] = True

        for k in mp.keys():
            mp[k] = False

#calculation
    for k in range(20):
        for i in range(len(files)):
            path = "./source/" + files[i]
            f = open(path,"r")
            content = f.read()
            content_list = re.split("\s|\n",content)
            if(sum.get(files[i],None) == None): sum[files[i]] = 0

            for j in range(len(content_list)):
                if(content_list[j].find(".html") != -1):
                    if(sum.get(content_list[j],None) == None): sum[content_list[j]] = 0
                    sum[content_list[j]] += score[files[i]] / books[files[i]]

                    #print(files[i],content_list[j],score[content_list[j]],score[files[i]],books[files[i]])


        for i in range(len(files)):
            if(sum.get(files[i],None) != None):
                score[files[i]] = 0.15 + 0.85 * sum[files[i]]
                sum[files[i]] = 0

    #normalization
    for i in range(len(files)):
        score_nor[files[i]] = score[files[i]] / max(score.values())
        query_score_nor[files[i]] = query_score[files[i]] / max(query_score.values())
        res[files[i]] = score_nor[files[i]] + query_score_nor[files[i]]

    print("word page score")
    for i in range(len(files)):
        print("{:.3}".format(query_score_nor[files[i]]),':',"{:.3}".format(score_nor[files[i]]),':',"{:.3}".format(res[files[i]]),':',files[i])
