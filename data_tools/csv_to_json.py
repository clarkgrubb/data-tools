#!/usr/bin/env python3
import argparse
import csv
import json
import sys

ENCODING = 'utf-8'


def csv_to_json(input_stream, output_stream, header_str, delimiter, quotechar):
    reader = csv.reader(input_stream, delimiter=delimiter, quotechar=quotechar)

    if header_str:
        header = header_str.split(',')
    else:
        header = reader.__next__()

    for row in reader:
        output_stream.write(json.dumps(dict(zip(header, row))))
        output_stream.write('\n')


def main():
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
        f = open(args.input, encoding=ENCODING)
    else:
        f = sys.stdin

    csv_to_json(f, sys.stdout, args.header, args.delimiter, args.quotechar)

if __name__ == '__main__':
    main()
