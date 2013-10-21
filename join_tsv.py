#!/usr/bin/env python

import argparse
import codecs
import collections
import os
import sys

ENCODING = 'utf-8'
BIG_FIRST = 1
BIG_LAST = 2
JOIN_INNER = 1
JOIN_LEFT = 2
JOIN_RIGHT = 3
JOIN_FULL = 4
DEFAULT_OUTER_NULL = ''
outer_null = None

sys.stdout = codecs.getwriter(ENCODING)(sys.stdout)
sys.stderr = codecs.getwriter(ENCODING)(sys.stderr)


def header_and_column_to_rows(path, column):
    with codecs.open(path, encoding=ENCODING) as f:
        column_to_rows = collections.defaultdict(list)

        header = f.readline().rstrip('\r\n').split('\t')
        row_len = len(header)
        column_index = None
        try:
            column_index = header.index(column)
        except ValueError:
            raise Exception('{} does not have a {} column'.format(
                path, column))
        del(header[column_index])

        for lineno, line in enumerate(f, start=2):
            fields = line.rstrip('\r\n').split('\t')
            if len(fields) != row_len:
                raise Exception('row {} does not have {} fields: {}'.format(
                    lineno,
                    row_len,
                    line))
            column_value = fields[column_index]
            del(fields[column_index])
            column_to_rows[column_value].append(fields)

    return header, column_to_rows


def print_row(join_value, fields1, fields2, f):
    f.write(join_value)
    f.write('\t')
    f.write('\t'.join(fields1))
    f.write('\t')
    f.write('\t'.join(fields2))
    f.write('\n')


def join_tsv(left_join_column,
             right_join_column,
             null,
             join_type,
             path1,
             path2,
             output_stream):

    if os.path.getsize(path1) > os.path.getsize(path2):
        big, small, file_order = path1, path2, BIG_FIRST
        big_join_column = left_join_column
        small_join_column = right_join_column
    else:
        big, small, file_order = path2, path1, BIG_LAST
        big_join_column = right_join_column
        small_join_column = left_join_column

    outer_join_big, outer_join_small = False, False

    small_header, column_to_rows = header_and_column_to_rows(small,
                                                             small_join_column)

    EMPTY_SMALL_HEADER = [outer_null] * len(small_header)

    if join_type == JOIN_FULL:
        outer_join_big, outer_join_small = True, True
    elif join_type == JOIN_LEFT:
        if file_order == BIG_FIRST:
            outer_join_big = True
        else:
            outer_join_small = True
    elif join_type == JOIN_RIGHT:
        if file_order == BIG_FIRST:
            outer_join_small = True
        else:
            outer_join_big = True

    with codecs.open(big, encoding=ENCODING) as f:
        big_header = f.readline().rstrip('\r\n').split('\t')
        row_len = len(big_header)
        column_index = None
        try:
            column_index = big_header.index(big_join_column)
        except ValueError:
            raise Exception('{} does not have a {} column'.format(
                big, coumn))
        del(big_header[column_index])
        EMPTY_BIG_HEADER = [outer_null] * len(big_header)

        print_row(left_join_column,
                  big_header if file_order == BIG_FIRST else small_header,
                  small_header if file_order == BIG_FIRST else big_header,
                  output_stream)

        # used if output_join_small is True
        join_values = set()

        for lineno, line in enumerate(f, start=2):
            big_fields = line.rstrip('\r\n').split('\t')
            if len(big_fields) != row_len:
                raise Exception('row {} does not have {} fields: {}'.format(
                    lineno,
                    row_line,
                    line))
            join_value = big_fields[column_index]
            del(big_fields[column_index])

            if join_value != null:
                small_rows = column_to_rows.get(join_value,
                                                [EMPTY_SMALL_HEADER]
                                                if outer_join_big
                                                else [])
                if outer_join_small:
                    join_values.add(join_value)
                for small_fields in small_rows:
                    print_row(
                        join_value,
                        big_fields if file_order == BIG_FIRST
                        else small_fields,
                        small_fields if file_order == BIG_FIRST
                        else big_fields,
                        output_stream)

        if outer_join_small:
            big_fields = EMPTY_BIG_HEADEr
            for join_value, small_rows in column_to_rows.iter_items():
                if join_value not in join_values:
                    for small_fields in small_rows:
                        print_row(
                            join_value,
                            big_fields if file_order == BIG_FIRST
                            else small_fields,
                            small_fields if file_order == BIG_FIRST
                            else big_fields,
                            output_stream)


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('files',
                        nargs='+',
                        metavar='TSV_FILE')
    parser.add_argument('--column', '-c', '-C',
                        dest='column')
    parser.add_argument('--left', '-l',
                        dest='left',
                        action='store_true',
                        default=False)
    parser.add_argument('--left-column', '-L',
                        dest='left_column',
                        default=None)
    parser.add_argument('--right', '-r',
                        dest='right',
                        action='store_true',
                        default=False)
    parser.add_argument('--right-column', '-R',
                        dest='right_column',
                        default=None)
    parser.add_argument('--full', '-f',
                        dest='full',
                        action='store_true',
                        default=False)
    parser.add_argument('--null', '-n',
                        dest='null',
                        default='')
    parser.add_argument('--outer-null', '-o',
                        dest='outer_null',
                        default=DEFAULT_OUTER_NULL)
    parser.add_argument('--no-null', '-N',
                        dest='no_null',
                        action='store_true',
                        default=False)
    args = parser.parse_args()

    if len(args.files) != 2:
        sys.stderr.write('must be two files, not {}\n'.format(args.files))
        parser.print_help()
        sys.exit(1)

    left_join_column = None
    right_join_column = None

    if args.column:
        if args.left_column or args.right_column:
            sys.stderr.write('--column flag is incompatible with --left-column'
                             ' and --right-column flags\n')
            parser.print_help()
            sys.exit(1)
        left_join_column, right_join_column = args.column, args.column
    if args.left_column:
        left_join_column = args.left_column
    if args.right_column:
        right_join_column = args.right_column

    if not left_join_column or not right_join_column:
        sys.stderr.write('must specify join column(s)\n')
        parser.print_help()
        sys.exit(1)

    join_type = JOIN_INNER
    flag_cnt = 0
    if args.left:
        join_type = JOIN_LEFT
        flag_cnt += 1
    if args.right:
        join_type = JOIN_RIGHT
        flag_cnt += 1
    if args.full:
        join_type = JOIN_FULL
        flag_cnt += 1

    if flag_cnt > 1:
        sys.stderr.write('left, right or full join flags are exclusive\n')
        parser.print_help()
        sys.exit(1)

    outer_null = args.outer_null

    join_tsv(left_join_column,
             right_join_column,
             None if args.no_null else args.null,
             join_type,
             args.files[0],
             args.files[1],
             sys.stdout)
