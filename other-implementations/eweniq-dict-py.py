#!/usr/bin/env python -tt

import sys


items = {}

for line in sys.stdin:
    line = line.rstrip()
    if line not in items:
        items[line] = True
        print(line)


