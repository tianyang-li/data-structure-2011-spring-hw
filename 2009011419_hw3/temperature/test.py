#!/usr/bin/python

import sys
import random

random.seed()

i = 0
while i != int(sys.argv[1]):
    print '%d %d %d' % (random.randint(-2147483648, 2147483647), random.randint(-2147483648, 2147483647), random.randint(-5000, 5000))
    i = i + 1
    
i = 0
while i != int(sys.argv[2]):
    x1 = random.randint(-2147483648, 2147483647)
    x2 = random.randint(-2147483648, 2147483647)
    y1 = random.randint(-2147483648, 2147483647)
    y2 = random.randint(-2147483648, 2147483647)
    if x1 < x2:
        if y1 < y2:
            print '%d %d %d %d' % (x1, y1, x2, y2)
        else:
            print '%d %d %d %d' % (x1, y2, x2, y1)
    else:
        if y1 < y2:
            print '%d %d %d %d' % (x2, y1, x1, y2)
        else:
            print '%d %d %d %d' % (x2, y2, x1, y1)
    i = i + 1
