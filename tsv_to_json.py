#!/usr/bin/env python

import json
import sys

header = sys.stdin.readline().rstrip('\r\n').split('\t')

for lineno, line in enumerate(sys.stdin):
    fields = line.rstrip('\r\n').split('\t')
    if len(fields) != len(header):
        raise Exception('incorrect number of fields at line {}: {}'.format(
            lineno,
            line))
    print(json.dumps(dict(zip(header, fields))))
