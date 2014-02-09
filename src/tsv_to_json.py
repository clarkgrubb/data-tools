#!/usr/bin/env python

import codecs
import json
import sys

ENCODING = 'utf-8'
NEWLINE_CHARS = u'\f\n\r\v\x85\u2028\u2029'

sys.stdin = codecs.getreader(ENCODING)(sys.stdin)
sys.stdout = codecs.getwriter(ENCODING)(sys.stdout)
sys.stderr = codecs.getwriter(ENCODING)(sys.stderr)

if len(sys.argv) == 1:
    f = sys.stdin
elif len(sys.argv) == 2:
    if sys.argv[1] == '--help':
        sys.stderr.write('USAGE: tsv-to-json [TSV_FILE]\n')
        sys.exit(1)
    f = codecs.open(sys.argv[1], encoding=ENCODING)
else:
    sys.sderr.write("USAGE: tsv_to_json.py [FILE]")
    sys.exit(1)

header = f.readline().rstrip(NEWLINE_CHARS).split('\t')

for lineno, line in enumerate(f):
    fields = line.rstrip(NEWLINE_CHARS).split('\t')
    if len(fields) != len(header):
        raise Exception('incorrect number of fields at line {}: {}'.format(
            lineno,
            line))
    print(json.dumps(dict(zip(header, fields))))
