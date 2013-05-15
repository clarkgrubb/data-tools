#!/usr/bin/env python

# Convert CSV and similar formats to TSV (tab and newline delimited).

import argparse
import csv
import re
import sys

STRIPPER_CHARS = "\n\r\t"
PROHIBITED_REGEX = re.compile('([\n\r\t])')
SPACES_REGEX = re.compile(' +')


def stripper(row):
    return [field.translate(None, STRIPPER_CHARS) for field in row]


def escape(field):

    str_builder = []

    for ch in field:
        if ch == '\\':
            str_builder.append('\\')
            str_builder.append('\\')
        elif ch == '\n':
            str_builder.append('\\')
            str_builder.append('n')
        elif ch == '\r':
            str_builder.append('\\')
            str_builder.append('r')
        elif ch == '\t':
            str_builder.append('\\')
            str_builder.append('t')
        else:
            str_builder.append(ch)


    return ''.join(str_builder)


def escaper(row):
    return [escape(field) for field in row]


def replacer(row):

    return [PROHIBITED_REGEX.sub(' ', field)
            for field
            in row]


def squeezer(row):

    return [SPACES_REGEX.sub(' ', PROHIBITED_REGEX.sub(' ', field))
            for field
            in row]


def detecter(row):
    for field in row:
        if PROHIBITED_REGEX.search(field):
            raise ValueError('prohibited character in field: {}'.format(field))

    return row


def csv_to_tsv(input_stream,
               output_stream,
               delimiter=',',
               quotechar='"',
               sanitizer=stripper):

    rows = csv.reader(input_stream,
                      delimiter=delimiter,
                      quotechar=quotechar)

    lineno = 1
    for row in rows:
        try:
            output_stream.write('\t'.join(sanitizer(row)) + '\n')
            lineno += 1
        except ValueError as e:
            raise ValueError('{}: at line number: {}'.format(str(e), lineno))


if __name__ == '__main__':

    parser = argparse.ArgumentParser()

    parser.add_argument('--delimiter', '-d',
                        dest='delimiter',
                        default=',')
    parser.add_argument('--quotechar', '-q',
                        dest='quotechar',
                        default='"')
    parser.add_argument('--escape', '-e',
                        dest='escape',
                        action='store_const',
                        const=True)
    parser.add_argument('--strip', '-x',
                        dest='strip',
                        action='store_const',
                        const=True)
    parser.add_argument('--replace', '-r',
                        dest='replace',
                        action='store_const',
                        const=True)
    parser.add_argument('--squeeze', '-z',
                        dest='squeeze',
                        action='store_const',
                        const=True)

    args = parser.parse_args()

    exclusive_cnt = 0
    if args.escape:
        exclusive_cnt += 1
    if args.strip:
        exclusive_cnt += 1
    if args.replace:
        exclusive_cnt += 1
    if args.squeeze:
        exclusive_cnt += 1
    if exclusive_cnt > 1:
        raise Exception('The flags --escape, --strip, --replace, and --squeeze'
                        ' cannot be used together.')

    if args.escape:
        sanitizer = escaper
    elif args.strip:
        sanitizer = stripper
    elif args.replace:
        sanitizer = replacer
    elif args.squeeze:
        sanitizer = squeezer
    else:
        sanitizer = detecter

    csv_to_tsv(sys.stdin,
               sys.stdout,
               delimiter=args.delimiter,
               quotechar=args.quotechar,
               sanitizer=sanitizer)
