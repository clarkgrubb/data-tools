#!/usr/bin/env python

# Convert CSV and similar formats to TSV (tab and newline delimited).

import argparse
import codecs
import csv
import re
import sys

# Unicode Newline Guidelines:
#
# http://www.unicode.org/standard/reports/tr13/tr13-5.html

STRIPPER_CHARS = u"\f\n\r\t\v\u0085\u2028\u2029"
STRIPPER_TAB = {ord(ch): None for ch in STRIPPER_CHARS}
PROHIBITED_REGEX = re.compile(u'([\f\n\r\t\v\u0085\u2028\u2029])')
SPACES_REGEX = re.compile(' +')
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


def stripper(row):
    return [field.translate(STRIPPER_TAB) for field in row]


def escape(field):

    str_builder = []

    for ch in field:
        if ch == u'\\':
            str_builder.append(u'\\')
            str_builder.append(u'\\')
        elif ch == u'\f':
            str_builder.append(u'\\')
            str_builder.append(u'f')
        elif ch == u'\n':
            str_builder.append(u'\\')
            str_builder.append(u'n')
        elif ch == u'\r':
            str_builder.append(u'\\')
            str_builder.append(u'r')
        elif ch == u'\t':
            str_builder.append(u'\\')
            str_builder.append(u't')
        elif ch == u'\v':
            str_builder.append(u'\\')
            str_builder.append(u'v')
        elif ch == u'\u0085':
            str_builder.append(u'\\')
            str_builder.append(u'u0085')
        elif ch == u'\u2028':
            str_builder.append(u'\\')
            str_builder.append(u'u2028')
        elif ch == u'\u2029':
            str_builder.append(u'\\')
            str_builder.append(u'u2029')
        else:
            str_builder.append(ch)

    return ''.join(str_builder)


def escaper(row):
    return [escape(field) for field in row]


def replacer(row):

    return [PROHIBITED_REGEX.sub(u' ', field)
            for field
            in row]


def squeezer(row):

    return [SPACES_REGEX.sub(u' ', PROHIBITED_REGEX.sub(u' ', field))
            for field
            in row]


def detecter(row):
    for field in row:
        if PROHIBITED_REGEX.search(field):
            raise ValueError('prohibited character in field: {}'.format(field))

    return row


def csv_to_tsv(input_stream,
               output_stream,
               header,
               delimiter=u',',
               quotechar=u'"',
               sanitizer=stripper):

    rows = unicode_csv_reader(input_stream,
                              delimiter=delimiter,
                              quotechar=quotechar)

    if header:
        output_stream.write(u'\t'.join(header.split(u',')) + u'\n')
    for row in rows:
        output_stream.write(u'\t'.join(sanitizer(row)) + u'\n')


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
    parser.add_argument('--header',
                        dest='header',
                        metavar='NAME[,NAME..]')
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
               args.header,
               delimiter=args.delimiter,
               quotechar=args.quotechar,
               sanitizer=sanitizer)
