#!/usr/bin/env python -tt

import sys


items = set()

for line in sys.stdin:
    line = line.rstrip()
    if line not in items:
        items.add(line)
        print(line)


