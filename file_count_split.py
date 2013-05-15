#!/usr/bin/env python

import argparse
import sys


def split(input_stream, prefix, cnt):

    suffix_fmt = '%0{}d'.format(len(str(cnt - 1)))

    filehandles = [open('{}{}'.format(prefix, suffix_fmt % i), 'w')
                   for i
                   in range(0, cnt)]

    for i, line in enumerate(input_stream):
        filehandles[i % cnt].write(line)

    for f in filehandles:
        f.close()


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('--count', '-c', dest='count', type=int, required=True,
                        help='Number of output files to create.')
    parser.add_argument('--file', '-f', dest='file', required=True,
                        help='Path of the input file to split.')
    parser.add_argument('--prefix', '-p', dest='prefix', required=True,
                        help='Prefix for the output files.')

    args = parser.parse_args()

    if args.file:
        with open(args.file) as f:
            split(f, args.prefix, args.count)
    else:
        split(sys.stdin, args.prefix, args.count)
