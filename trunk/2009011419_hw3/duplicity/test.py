#!/usr/bin/python

import sys
import random

random.seed()

i = 1
while i != int(sys.argv[1]):
    len = random.randint(1, 40)
    j = 0
    while j != len:
        sys.stdout.write("%c" % chr(random.randint(ord('a'), ord('z'))))
        j = j + 1
    print "\n",
    i = i + 1



