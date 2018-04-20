#!/usr/bin/python3
import os
def openDir(path,fileTxt):
    if not os.path.exists(path):
        print "path is fail"
        return -1
    else:
        listd = os.listdir(path)
        print listd
        i = 0
        for i in listd:
            if i == fileTxt:
                return fileTxt
    return -1

def copyFile(rFileTxt,wFileTxt):
    file_1 = open(rFileTxt,"r")
    file_2 = open(wFileTxt,"w")
    while 1:    
        rstr=file_1.read(20)
        if rstr:
            print rstr
            file_2.write(rstr)
        else:
            break
    file_1.close()
    file_2.close()
def startCopy(path1,fileTxt1,path2,fileTxt2):
    rFileT = openDir(path1,fileTxt1)
    if rFileT == 0:
        print "path1 fileTxt1 is no exist"
        return
    else:
        rFileT = path1+fileTxt1
    wFileT = openDir(path2,fileTxt2)
    if wFileT == 0:
        wFileT = "./test2.txt"
    else:
        wFileT = path2+fileTxt2
    copyFile(rFileT,wFileT)
    return 0
startCopy("./","test1.txt","../","test2.txt");
