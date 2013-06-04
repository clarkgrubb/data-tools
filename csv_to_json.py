#!/usr/bin/env python

import argparse
import csv
import json
import sys

parser = argparse.ArgumentParser()

parser.add_argument('--delimiter', '-d',
                    dest='delimiter',
                    default=',')
parser.add_argument('--quotechar', '-q',
                    dest='quotechar',
                    default='"')

args = parser.parse_args()


rows = csv.DictReader(sys.stdin,
                      delimiter=args.delimiter,
                      quotechar=args.quotechar)
for row in rows:
    print(json.dumps(row))
