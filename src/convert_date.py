#!/usr/bin/env python

import argparse
import datetime
import sys

DEFAULT_FMT1 = '%Y-%m-%dT%H:%M:%S'
DEFAULT_FMT2 = '%s'


def convert(input_fmt, output_fmt, s):
    if input_fmt == '%s':
        dt = datetime.datetime.fromtimestamp(int(s))
    else:
        dt = datetime.datetime.strptime(s, input_fmt)

    return dt.strftime(output_fmt)


def convert_date(fin, fout, input_fmt, output_fmt, column):
    for lineno, line in enumerate(fin, start=1):
        row = line.rstrip().split('\t')
        if column > len(row) - 1:
            sys.stderr.write(
                "Line number {} does not have {} columns\n".format(
                    lineno, column))
            sys.exit(1)
        try:
            row[column] = convert(input_fmt, output_fmt, row[column])
        except ValueError as e:
            sys.stderr.write(
                "On line number {}: {}\n".format(
                    lineno, str(e)))
            sys.exit(1)
        fout.write('\t'.join(row))
        fout.write('\n')


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('--header', '-H',
                        dest='header',
                        action='store_true')
    parser.add_argument('--input-format', '-i',
                        dest='input_fmt',
                        default=None)
    parser.add_argument('--output-format', '-o',
                        dest='output_fmt',
                        default=None)
    parser.add_argument('--column', '-c',
                        dest='column',
                        type=int,
                        default=0)
    args = parser.parse_args()

    input_fmt = args.input_fmt
    output_fmt = args.output_fmt

    if input_fmt is None:
        if output_fmt == DEFAULT_FMT1:
            input_fmt = DEFAULT_FMT2
        elif output_fmt == DEFAULT_FMT2:
            input_fmt = DEFAULT_FMT1
        else:
            sys.stderr.write('Use -i to set strftime-style input format.\n')
            sys.exit(1)

    if output_fmt is None:
        if input_fmt == DEFAULT_FMT1:
            output_fmt = DEFAULT_FMT2
        elif input_fmt == DEFAULT_FMT2:
            output_fmt = DEFAULT_FMT1
        else:
            sys.stderr.write('Use -o to set strftime-style output format.\n')
            sys.exit(1)

    if args.header:
        header = sys.stdin.readline()
        sys.stdout.write(header)

    convert_date(sys.stdin,
                 sys.stdout,
                 input_fmt,
                 output_fmt,
                 args.column)

if __name__ == '__main__':
    main()
