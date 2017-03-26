#!/usr/bin/env python3
import argparse
import csv
import re
import sys
from typing import IO

import bs4

RX_TH_OR_TD = re.compile(r'^th|td$')


def html_table_to_csv(input_f: IO, output_f: IO, table_num: int) -> None:
    doc = bs4.BeautifulSoup(input_f.read(), 'html5lib')
    tables = doc.find_all('table')
    try:
        table = tables[table_num]
        trows = table.find_all('tr')
        csv_writer = csv.writer(output_f)
        for trow in trows:
            cells = trow.find_all(RX_TH_OR_TD)
            csv_writer.writerow([cell.text.strip() for cell in cells])
    except IndexError:
        sys.stderr.write('ERROR: no table at index {}\n'.format(table_num))
        sys.exit(1)


if __name__ == '__main__':
    parser = argparse.ArgumentParser()
    parser.add_argument('--table', '-t',
                        dest='table',
                        type=int,
                        default=0)
    parser.add_argument('input_path', nargs='?', default='')
    args = parser.parse_args()

    if args.input_path:
        with open(args.input_path) as f:
            html_table_to_csv(f, sys.stdout, args.table)
    else:
        html_table_to_csv(sys.stdin, sys.stdout, args.table)
