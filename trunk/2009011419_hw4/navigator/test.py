#!/usr/bin/python

import sys
import random
import string

print "%s %d" % (sys.argv[1], int(sys.argv[1]) * (int(sys.argv[1]) - 1) / 2)

i = 0
while i < int(sys.argv[1]):
    j = i + 1
    while j < int(sys.argv[1]):
        print "%d %d %d" % (10, i, j)
        j = j + 1
    i = i + 1
