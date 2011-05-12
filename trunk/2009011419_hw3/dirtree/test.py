#!/usr/bin/python

import sys
import random
import string

char_set = string.ascii_lowercase + string.digits

def RandPath():
    str = ''.join(random.choice(char_set) for x in range(random.randint(1, 10)))
    cont = ''.join(random.choice(char_set) for x in range(random.randint(1, 10)))
    while (len(str) + len(cont)) <= 254:
        str = str + '/' + cont
        cont = ''.join(random.choice(char_set) for x in range(random.randint(1, 10)))
    print str

i = 0
while i != int(sys.argv[1]):
    i = i + 1
    RandPath()
