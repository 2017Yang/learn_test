#!/usr/bin/python3

import urllib
import os
import re

def getHtml(url):
     respondse = urllib.urlopen(url)
     html = respondse.read().decode('utf-8')
     return html
     
def getImg(html):
    path = "image"
    reg = 'src="(.+?\.jpg)" alt='
    imgre = re.compile(reg)
    imglist = re.findall(imgre, html)
    if not os.path.exists(path): 
        os.mkdir(path,0755) 
    i = 0 
    for link in imglist: 
       # urllib.urlretrieve(link, '%s.jpg' % i)
       filename = 'image//' + str(i)+ '.jpg' 
       with open(filename, 'w') as file: urllib.urlretrieve(link, filename)
       i += 1 
    return imglist
html = getHtml("http://www.runoob.com/python3/python3-reg-expressions.html");
print getImg(html)