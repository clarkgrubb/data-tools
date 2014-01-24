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


def utf_8_encoder(unicode_csv_data):
    for line in unicode_csv_data:
        yield line.encode('utf-8')


def unicode_csv_reader(unicode_csv_data, dialect=csv.excel, **kwargs):
    csv_reader = csv.reader(utf_8_encoder(unicode_csv_data),
                            dialect=dialect, **kwargs)
    for row in csv_reader:
        yield [unicode(cell, 'utf-8') for cell in row]


def csv_to_json(input_stream, output_stream, header_str, delimiter, quotechar):
    reader = unicode_csv_reader(f,
                                delimiter=args.delimiter,
                                quotechar=args.quotechar)

    if header_str:
        header = header_str.split(',')
    else:
        header = reader.next()

    for row in reader:
        print(json.dumps(dict(zip(header, row))))


if __name__ == '__main__':
    parser = argparse.ArgumentParser()

    parser.add_argument('input', nargs='?')
    parser.add_argument('--delimiter', '-d',
                        dest='delimiter',
                        default=',')
    parser.add_argument('--header',
                        dest='header',
                        metavar='NAME[,NAME..]')
    parser.add_argument('--quotechar', '-q',
                        dest='quotechar',
                        default='"')

    args = parser.parse_args()

    if args.input:
        f = codecs.open(args.input, encoding=ENCODING)
    else:
        f = sys.stdin

    csv_to_json(f, sys.stdout, args.header, args.delimiter, args.quotechar)
