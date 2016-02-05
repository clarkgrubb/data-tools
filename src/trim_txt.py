#!/usr/bin/env python
import sys

for line in sys.stdin:
    line = line.rstrip('\n\r \t')
    sys.stdout.write(line)
    sys.stdout.write('\n')
