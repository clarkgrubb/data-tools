#!/usr/bin/env python

import argparse
import codecs
import datetime
import StringIO
import csv
import os
import pprint
import sys
import xlrd

DATE_FMT = '%Y-%m-%dT%H:%M:%S'
ENCODING = 'utf-8'
CSV_SUFFIX = '.csv'
PP = pprint.PrettyPrinter()


class UnicodeWriter:
    """
    This class is lifted from http://docs.python.org/2/library/csv.html
    """

    def __init__(self, f, dialect=csv.excel, encoding=ENCODING, **kwds):
        self.queue = StringIO.StringIO()
        self.writer = csv.writer(self.queue, dialect=dialect, **kwds)
        self.stream = f
        self.encoder = codecs.getincrementalencoder(encoding)()

    def writerow(self, row):
        self.writer.writerow([s.encode(ENCODING) for s in row])
        data = self.queue.getvalue()
        data = data.decode(ENCODING)
        data = self.encoder.encode(data)
        self.stream.write(data)
        self.queue.truncate(0)

    def writerows(self, rows):
        for row in rows:
            self.writerow(row)


def list_xlsx_sheets(xlsx_path, output_stream):
    book = xlrd.open_workbook(xlsx_path)
    for sheet in sorted(book.sheet_names()):
        output_stream.write(sheet)
        output_stream.write('\n')


def sheet_name_to_filename(sheet_name):
    return sheet_name + CSV_SUFFIX


def cell_to_str(cell, date_fmt, datemode):
    if cell.ctype == xlrd.XL_CELL_DATE:
        dt = datetime.datetime(*xlrd.xldate_as_tuple(cell.value, datemode))
        return dt.strftime(date_fmt)
    else:
        return unicode(cell.value)


def xlsx_book_to_csv(book, sheet_path, sheet_name, date_fmt):
    sheet = book.sheet_by_name(sheet_name)
    if sheet_path == '-':
        f = sys.stdout
    else:
        f = open(sheet_path, 'wb')
    csvw = UnicodeWriter(f)
    for rownum in range(0, sheet.nrows):
        row = [cell_to_str(cell, date_fmt, book.datemode)
               for cell
               in sheet.row(rownum)]
        csvw.writerow(row)
    if sheet_path != '-':
        f.close()


def xlsx_path_to_csv(xlsx_path, sheet_path, sheet_name, date_fmt):
    book = xlrd.open_workbook(xlsx_path)
    xlsx_book_to_csv(book, sheet_path, sheet_name, date_fmt)


def xlsx_path_to_csvs(xlsx_path, dir_path, date_fmt):
    book = xlrd.open_workbook(xlsx_path)
    for sheet_name in book.sheet_names():
        sheet_path = os.path.join(dir_path,
                                  sheet_name_to_filename(sheet_name))
        xlsx_book_to_csv(book, sheet_path, sheet_name, date_fmt)


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('paths',
                        nargs='*',
                        metavar='PATH')
    parser.add_argument('--date-format', '-d',
                        dest='date_fmt',
                        default=DATE_FMT)
    parser.add_argument('--sheet', '-s',
                        dest='sheet')
    parser.add_argument('--list', '-l',
                        dest='list',
                        action='store_true')
    args = parser.parse_args()

    if args.list:
        if len(args.paths) != 1:
            raise Exception("USAGE: xlsx-to-csv --list XLSX_FILE")
        list_xlsx_sheets(args.paths[0], sys.stdout)
    elif args.sheet:
        if len(args.paths) == 1:
            xlsx_path = args.paths[0]
            output_path = sheet_name_to_filename(args.sheet)
        elif len(args.paths) == 2:
            xlsx_path = args.paths[0]
            output_path = args.paths[1]
        else:
            raise Exception("USAGE xlsx-to-csv --sheet=NAME XLSX_FILE "
                            "[OUTPUT_FILE]")
        xlsx_path_to_csv(xlsx_path, output_path, args.sheet, args.date_fmt)
    else:
        if len(args.paths) != 2:
            raise Exception("USAGE: xlsx-to-csv XLSX_FILE OUTPUT_DIR")
        if os.path.exists(args.path[1]):
            sys.stderr.write(
                'Something is already at the output path: {}\n'.format(
                    args.path[1]))
            sys.exit(1)
        xlsx_path_to_csvs(args.paths[0], args.paths[1], args.date_fmt)
