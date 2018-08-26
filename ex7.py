#Ex7
#ID: s1240148
#Name: Shigeki Kobayashi
#Date: 07/25/2018

import numpy as np
import os,sys
import re
src = './source'

#these are files in source directory
files = os.listdir(src)
score = {}
#books are counter of document
books = {}
map_graph = {}
sum = {}

if __name__ == "__main__":
#initialization
    for i in range(len(files)):
        #create score[files[i]]
        score[files[i]] = 1.0
        path = "./source/" + files[i]
        f = open(path,"r")
        content = f.read()
        #content_list are list of contents located in files located in source directory
        content_list = re.split("\s|\n",content)
        for j in range(len(content_list)):
            if(content_list[j].find(".html") != -1):
                #create score[content_list[i]]
                score[content_list[j]] = 1.0
                #create books[files[i]]
                if books.get(files[i],None) == None: books[files[i]] = 1
                else: books[files[i]] += 1

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

    for i in range(len(files)):
        print("file = ",files[i],"score = ",score[files[i]] / max(score.values()))
