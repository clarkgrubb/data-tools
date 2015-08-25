#!/usr/bin/env python

import json
import sys

data = json.loads(sys.stdin.read())

for element in data:
    sys.stdout.write(json.dumps(element))
    sys.stdout.write('\n')
