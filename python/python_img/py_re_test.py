#!/usr/bin/python
import re

listRe = "www.baidu.con"
ReMatch = re.match("www",listRe,0)
print ReMatch.group()
print ReMatch.group(1)
