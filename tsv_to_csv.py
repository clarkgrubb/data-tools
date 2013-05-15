#!/usr/bin/env python

# Convert TSV (tab and newline delimited) to CSV.

import argparse
import csv
import re
import sys


def unescaper(field):

    str_builder = []

    backslashed = False

    for ch in field:
        if ch == '\\':
            backslashed = True
        else:
            if backslashed:
                if ch == 'n':
                    str_builder.append('\n')
                elif ch == 'r':
                    str_builder.append('\r')
                elif ch == 't':
                    str_builder.append('\t')
                elif ch == '\\':
                    str_builder.append('\\')
                else:
                    # if correctly escaped, this case
                    # won't happen.
                    str_builder.append(ch)
            else:
                str_builder.append(ch)
            backslashed = False

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
        row = line.rstrip('\n\r').split('\t')
        if unescape:
            row = [unescaper(field) for field in row]
        csv_writer.writerow(row)


if __name__ == '__main__':

    parser = argparse.ArgumentParser()

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

    tsv_to_csv(sys.stdin,
               sys.stdout,
               delimiter=args.delimiter,
               quotechar=args.quotechar,
               unescape=args.unescape)
