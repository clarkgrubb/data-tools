#!/usr/bin/env python

import argparse
import datetime
import re
import sys

import pprint
PP = pprint.PrettyPrinter()

REPORT_STATS = True
FILL_SEPARATOR = ','
DEFAULT_FILL_VALUE = '0'
RX_DIRECTIVE = re.compile(r'%.')

YEAR_DIRECTIVES = set('%y %Y %g %G'.split())
MONTH_DIRECTIVES = set('%b %B %C %d %d %h %m'.split())
DAY_DIRECTIVES = set('%a %A %D %j %u %U %v %V %w %W %x'.split())
HOUR_DIRECTIVES = set('%H %i %k %l %p'.split())
MINUTE_DIRECTIVES = set('%M %R'.split())
SECOND_DIRECTIVES = set('%c %r %s %S %T %X'.split())


def make_year_iterator(start,
                       end,
                       fmt):
    def date_iter(start_i, end_i):
        i = start_i
        while True:
            if i > end_i:
                return
            dt = datetime.datetime.strptime(str(i), fmt)
            yield dt
            i += 1

    return date_iter(int(start), int(end))


def make_month_iterator(start,
                        end,
                        fmt):

    start_yyyy = int(start[0:4])
    start_mm = int(start[4:6])
    end_yyyy = int(end[0:4])
    end_mm = int(end[4:6])

    def date_iter(start_yyyy, start_mm, end_yyyy, end_mm):
        yyyy = start_yyyy
        mm = start_mm
        while True:
            if yyyy > end_yyyy or (yyyy == end_yyyy and mm > end_mm):
                return
            dt = datetime.datetime.strptime('%04d%02d' % (yyyy, mm), fmt)
            yield dt
            mm += 1
            if mm == 13:
                mm = 1
                yyyy += 1

    return date_iter(start_yyyy, start_mm, end_yyyy, end_mm)


def make_date_iterator(start_dt,
                       end_dt,
                       delta):

    def date_iter(start_dt, end_dt):
        dt = start_dt
        while True:
            if dt > end_dt:
                return
            yield dt
            dt += delta

    return date_iter(start_dt, end_dt)


def load_rows(input_path, date_column, no_header):
    date_to_line = {}
    header = None
    max_columns = 0
    with open(input_path) as f:
        if not no_header:
            header = f.readline()
        for line in f:
            data = line.rstrip().split('\t')
            if len(data) > max_columns:
                max_columns = len(data)
            date_to_line[data[date_column]] = line.rstrip()

    return date_to_line, header, max_columns


def date_fill(input_path,
              date_column,
              no_header,
              fill_values,
              start,
              end,
              output_fmt,
              output_stream):

    date_to_line, header, max_column = load_rows(input_path,
                                                 date_column,
                                                 no_header)

    if fill_values:
        fill_row = fill_values.split(FILL_SEPARATOR)
    else:
        fill_row = [DEFAULT_FILL_VALUE] * max_column

    start_dt = None
    end_dt = None
    for date in date_to_line.keys():
        dt = datetime.datetime.strptime(date, output_fmt)
        if not start_dt or dt < start_dt:
            start_dt = dt
        if not end_dt or dt > end_dt:
            end_dt = dt

    if start:
        start_dt = datetime.datetime.strptime(start, output_fmt)

    if end:
        end_dt = datetime.datetime.strptime(end, output_fmt)

    date_iter = None

    directives = set(RX_DIRECTIVE.findall(output_fmt))

    if directives & SECOND_DIRECTIVES:
        delta = datetime.timedelta(seconds=1)
        trunc_fmt = '%Y%m%d%H%M%S'
    elif directives & MINUTE_DIRECTIVES:
        delta = datetime.timedelta(minutes=1)
        trunc_fmt = '%Y%m%d%H%M'
    elif directives & HOUR_DIRECTIVES:
        delta = datetime.timedelta(hours=1)
        trunc_fmt = '%Y%m%d%H'
    elif directives & DAY_DIRECTIVES:
        delta = datetime.timedelta(days=1)
        trunc_fmt = '%Y%m%d'
    elif directives & MONTH_DIRECTIVES:
        trunc_fmt = '%Y%m'
        date_iter = make_month_iterator(start_dt.strftime(trunc_fmt),
                                        end_dt.strftime(trunc_fmt),
                                        output_fmt)
    elif directives & YEAR_DIRECTIVES:
        trunc_fmt = '%Y'
        date_iter = make_year_iterator(start_dt.strftime(trunc_fmt),
                                       end_dt.strftime(trunc_fmt),
                                       output_fmt)
    else:
        raise Exception('no recognized directives in format: {}'.format(
            output_fmt))

    if not date_iter:
        start_s = start_dt.strftime(trunc_fmt)
        start_dt = datetime.datetime.strptime(start_s, trunc_fmt)

        end_s = end_dt.strftime(trunc_fmt)
        end_dt = datetime.datetime.strptime(end_s, trunc_fmt)

        date_iter = make_date_iterator(start_dt, end_dt, delta)

    line_count = 0
    fill_count = 0
    if header is not None:
        output_stream.write(header)
    for dt in date_iter:
        date = dt.strftime(output_fmt)
        line = date_to_line.get(date, None)
        if line is None:
            fill_count += 1
            row = list(fill_row)
            row[date_column] = date
            line = '\t'.join(row)
        output_stream.write(line)
        output_stream.write('\n')
        line_count += 1
    if REPORT_STATS:
        output_stream.flush()
        sys.stderr.write(
            'retained non-header lines: {}\n'
            'filled lines: {}\n'
            'dropped lines: {}\n'.format(
                line_count,
                fill_count,
                len(date_to_line.keys()) - (line_count - fill_count)))


parser = argparse.ArgumentParser()

parser.add_argument('--start', '-s', help='YYYY[MM[DD[HH[MI[SS]]]]]',
                    dest='start',
                    default=None)
parser.add_argument('--end', '-e', help='YYYY[MM[DD[HH[MI[SS]]]]]',
                    dest='end',
                    default=None)
parser.add_argument('--date-column', '-d',
                    help='column containing date: first column is 0',
                    type=int,
                    dest='date_column')
parser.add_argument('--format', '-f',
                    dest='format', help='strftime style format for output',
                    default=None)
parser.add_argument('--no-header', '-H', help='if file has no header',
                    dest='no_header',
                    action='store_true')
parser.add_argument('--input-path', '-i',
                    dest='input_path', help='input path for TSV',
                    required=True)
parser.add_argument('--fill-values', '-v',
                    help='comma-separated list of fill values',
                    dest='fill_values',
                    default='')

args = parser.parse_args()


date_fill(args.input_path,
          args.date_column,
          args.no_header,
          args.fill_values,
          args.start,
          args.end,
          args.format,
          sys.stdout)
