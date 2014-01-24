#!/usr/bin/env python

import argparse
import datetime
import re
import sys

import pprint
PP = pprint.PrettyPrinter()

REGEX_INPUT_DATE = re.compile('^\d{4,14}$')
WEEKDAY_TO_NUMBER = {
    'mon': 1,
    'tue': 2,
    'wed': 3,
    'thu': 4,
    'fri': 5,
    'sat': 6,
    'sun': 7
}


def check(dt, fmt, regex_date_filter):
    if not regex_date_filter:
        return True
    if regex_date_filter.match(dt.strftime(fmt)):
        return True
    return False


def make_year_iterator(start,
                       end,
                       regex_date_filter,
                       fmt):
    def date_iter(start_i, end_i):
        i = start_i
        while True:
            if i > end_i:
                return
            dt = datetime.datetime.strptime(str(i), fmt)
            if check(dt, fmt, regex_date_filter):
                yield dt
            i += 1

    return date_iter(int(start), int(end))


def make_month_iterator(start,
                        end,
                        regex_date_filter,
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
            if check(dt, fmt, regex_date_filter):
                yield dt
            mm += 1
            if mm == 13:
                mm = 1
                yyyy += 1

    return date_iter(start_yyyy, start_mm, end_yyyy, end_mm)


def make_date_iterator(start,
                       end,
                       weekday_numbers,
                       regex_date_filter,
                       delta,
                       fmt):

    start_dt = datetime.datetime.strptime(start, fmt)
    end_dt = datetime.datetime.strptime(end, fmt)

    def date_iter(start_dt, end_dt):
        dt = start_dt
        while True:
            if dt > end_dt:
                return
            if not weekday_numbers:
                if check(dt, fmt, regex_date_filter):
                    yield dt
            else:
                weekday_number = int(dt.strftime('%u'))
                if weekday_number in weekday_numbers:
                    if check(dt, fmt, regex_date_filter):
                        yield dt
            dt += delta

    return date_iter(start_dt, end_dt)


def date_seq(start,
             end,
             weekdays,
             date_filter,
             output_fmt,
             output_stream):

    if len(start) != len(end):
        raise Exception('Start and end date must be same length')

    if not REGEX_INPUT_DATE.search(start):
        raise Exception(
            'Start date must be in YYYY[MM[DD[HH[MI[SS]]]]] format.')

    if not REGEX_INPUT_DATE.search(end):
        raise Exception('End date must be in YYYY[MM[DD[HH[MI[SS]]]]] format.')

    if weekdays:
        weekday_numbers = [WEEKDAY_TO_NUMBER[wkday.lower()[0:3]]
                           for wkday
                           in weekdays.split(',')]
    else:
        weekday_numbers = []

    regex_date_filter = re.compile(date_filter) if date_filter else None
    date_iter = None

    if len(start) == 4:
        fmt = '%Y'
        date_iter = make_year_iterator(start, end, regex_date_filter, fmt)
    elif len(start) == 6:
        fmt = '%Y%m'
        date_iter = make_month_iterator(start, end, regex_date_filter, fmt)
    elif len(start) == 8:
        delta = datetime.timedelta(days=1)
        fmt = '%Y%m%d'
    elif len(start) == 10:
        delta = datetime.timedelta(hours=1)
        fmt = '%Y%m%d%H'
    elif len(start) == 12:
        delta = datetime.timedelta(minutes=1)
        fmt = '%Y%m%d%H%S'
    elif len(start) == 14:
        delta = datetime.timedelta(seconds=1)
        fmt = '%Y%m%d%H%M%S'
    else:
        raise Exception('unexpected argument length: {}'.format(len(start)))

    if not date_iter:
        date_iter = make_date_iterator(start,
                                       end,
                                       weekday_numbers,
                                       regex_date_filter,
                                       delta,
                                       fmt)

    if output_fmt is None:
        output_fmt = fmt

    for dt in date_iter:
        output_stream.write(dt.strftime(output_fmt) + '\n')


parser = argparse.ArgumentParser()

parser.add_argument('start', help='YYYY[MM[DD[HH[MI[SS]]]]]')
parser.add_argument('end', help='YYYY[MM[DD[HH[MI[SS]]]]]')

parser.add_argument('--format', '-f',
                    dest='format', help='strftime style format for output',
                    default=None)

parser.add_argument('--regex', '-r',
                    dest='date_filter', help='date filter regex.',
                    default=None)

parser.add_argument('--weekdays', '-w',
                    dest='weekdays', help='comma separated: Sun,Mon,...',
                    default=None)

args = parser.parse_args()


date_seq(args.start,
         args.end,
         args.weekdays,
         args.date_filter,
         args.format,
         sys.stdout)
