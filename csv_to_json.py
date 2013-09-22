#!/usr/bin/env python

import argparse
import codecs
import csv
import json
import sys

ENCODING = 'utf-8'

sys.stdin = codecs.getreader(ENCODING)(sys.stdin)
sys.stdout = codecs.getwriter(ENCODING)(sys.stdout)
sys.stderr = codecs.getwriter(ENCODING)(sys.stderr)

parser = argparse.ArgumentParser()

parser.add_argument('input', nargs='?')
parser.add_argument('--delimiter', '-d',
                    dest='delimiter',
                    default=',')
parser.add_argument('--quotechar', '-q',
                    dest='quotechar',
                    default='"')

args = parser.parse_args()

if args.input:
    f = codecs.open(args.input, encoding=ENCODING)
else:
    f = sys.stdin

rows = csv.DictReader(f,
                      delimiter=args.delimiter,
                      quotechar=args.quotechar)
for row in rows:
    print(json.dumps(row))
