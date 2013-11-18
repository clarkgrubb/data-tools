#!/usr/bin/env python

import argparse
import subprocess
import sys
import tempfile


DELIMITER = '\t'


def line_count(path, header):
    line_count = 0
    with open(path) as f:
        for lineno, line in enumerate(f, start=0 if header else 1):
            line_count = lineno

    return line_count


def quantiles_to_positions(quantiles, n):
    return [int(quantile * n) for quantile in quantiles]


def quantile(path, column, quantiles, output_stream,
             no_header=False,
             numeric=False,
             sort=False):

    with tempfile.NamedTemporaryFile(delete=False) as tmp:

        if sort:
            # what about no_header=False?
            cmd = ['sort', '-t', '\t', '-k', '{},{}'.format(column, column)]
            if numeric:
                cmd.append('-n')
            cmd.append(path)
            p = subprocess.Popen(cmd, stdout=tmp)
            exit_status = p.wait()
            if exit_status != 0:
                raise Exception('ERROR failed to sort file')
            data_file = tmp.name
            header = False
        else:
            data_file = path
            header = not no_header

        n = line_count(data_file, header)
        positions = quantiles_to_positions(quantiles, n)

        last_field = None
        with open(data_file) as f:
            if header:
                line = f.readline()
            for lineno, line in enumerate(f, start=1):
                fields = line.rstrip('\r\n').split(DELIMITER)
                field = float(fields[column - 1]) if numeric else fields[column - 1]
                if last_field and last_field > field:
                    # TODO turn this into a single warning
                    raise Exception('file not sorted')
                last_field = field

                # TODO if fewer data that quantiles, we may have to print some multiple times
                if lineno in positions:
                    output_stream.write(str(field))
                    output_stream.write('\n')


if __name__ == '__main__':

    # TODO: option to print all, with asterisk or highlighting of quantiles?

    parser = argparse.ArgumentParser()
    parser.add_argument('input_file',
                        nargs=1,
                        metavar='PATH')

    parser.add_argument('-q', '--quantile', '--quantiles',
                        dest='quantiles')
    parser.add_argument('-c', '--column',
                        dest='column',
                        type=int,
                        help='one-based index of column containing data',
                        required=True)

    parser.add_argument('-H', '--no-header',
                        dest='no_header',
                        help='use if input file has no header',
                        action='store_true')
    parser.add_argument('-n', '--numeric',
                        dest='numeric',
                        help='if column contains numeric data',
                        action='store_true')
    parser.add_argument('-s', '--sort',
                        dest='sort',
                        help='if file needs sorting',
                        action='store_true')

    parser.add_argument('--median',
                        dest='median',
                        action='store_true')
    parser.add_argument('--quartile', '--quartiles',
                        dest='quartile',
                        action='store_true')
    parser.add_argument('--quintile', '--quintiles',
                        dest='quintile',
                        action='store_true')
    parser.add_argument('--decile', '--deciles',
                        dest='decile',
                        action='store_true')
    parser.add_argument('--percentile', '--percentiles',
                        dest='percentile',
                        action='store_true')

    args = parser.parse_args()

    quantiles = []
    if args.quantiles:
        quantiles.extend([float(q) for q in args.quantiles.split(',')])
    if args.median:
        quantiles.extend([0.5])
    if args.quartile:
        quantiles.extend([0.25, 0.5, 0.75])
    if args.quintile:
        quantiles.extend([0.2, 0.4, 0.6, 0.8])
    if args.decile:
        quantiles.extend([0.1 * i for i in range(1, 10)])
    if args.percentile:
        quantiles.extend([0.01 * i for i in range(1, 100)])

    if not quantiles:
        sys.stderr.write('ERROR: no quantiles specified\n')
        parser.print_help()
        sys.exit(1)

    # should quantiles be unique or sorted?
    # should quantiles be identified in output?

    quantile(args.input_file[0],
             args.column,
             quantiles,
             sys.stdout,
             args.no_header,
             args.numeric,
             args.sort)
