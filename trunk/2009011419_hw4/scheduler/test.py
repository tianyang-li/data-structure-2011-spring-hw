#!/usr/bin/python

import sys
import random
import string

char_set = string.ascii_lowercase + string.digits

random.seed()

def RandTask():
    print "%u %s" % (random.randint(1, 0x11111111), ''.join(random.choice(char_set) for x in range(random.randint(1, 8))))

print "%s %s" % (sys.argv[1], sys.argv[2])

i = 0
while i != int(sys.argv[1]):
    RandTask()
    i = i + 1
    