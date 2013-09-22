#!/usr/bin/env python

# Convert TSV (tab and newline delimited) to CSV.

import argparse
import codecs
import csv
import re
import sys

ENCODING = 'utf-8'
NEWLINE_CHARS = u'\f\n\r\v\x85\u2028\u2029'


def unescaper(field):

    str_builder = []

    backslashed = False

    i = 0
    while i < len(field):
        ch = field[i]
        if ch == '\\':
            backslashed = True
        else:
            if backslashed:
                if ch == 'f':
                    str_builder.append('\f')
                if ch == 'n':
                    str_builder.append('\n')
                elif ch == 'r':
                    str_builder.append('\r')
                elif ch == 't':
                    str_builder.append('\t')
                elif field[i:i + 5] == 'u2028':
                    i += 4
                    str_builder.append('\u2028')
                elif field[i:i + 5] == 'u2029':
                    i += 4
                    str_builder.append('\u2029')
                elif ch == 'v':
                    str_builder.append('\v')
                elif field[i:i + 3] == 'x85':
                    i += 4
                    str_builder.append('\x85')
                elif ch == '\\':
                    str_builder.append('\\')
                else:
                    # if correctly escaped, this case
                    # won't happen.
                    str_builder.append(ch)
            else:
                str_builder.append(ch)
            backslashed = False
        i += 1

    return ''.join(str_builder)


def tsv_to_csv(input_stream,
               output_stream,
               delimiter=',',
               quotechar='"',
               unescape=False):

    csv_writer = csv.writer(output_stream,
                            delimiter=delimiter,
                            quotechar=quotechar)

    for line in input_stream:
        row = line.rstrip(NEWLINE_CHARS).split('\t')
        if unescape:
            row = [unescaper(field) for field in row]
        csv_writer.writerow(row)


if __name__ == '__main__':

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
    parser.add_argument('--unescape', '-u',
                        action='store_const',
                        const=True)

    args = parser.parse_args()

    if args.input:
        f = codecs.open(args.input, encoding=ENCODING)
    else:
        f = sys.stdin
    tsv_to_csv(f,
               sys.stdout,
               delimiter=args.delimiter,
               quotechar=args.quotechar,
               unescape=args.unescape)
