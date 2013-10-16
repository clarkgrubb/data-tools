#!/usr/bin/env python

import sys

DELIMITER = '\t'


def trim_tsv(input_stream, output_stream):
    for line in input_stream:
        row = line.rstrip('\r\n').split(DELIMITER)
        data = [field.strip() for field in row]
        output_stream.write(DELIMITER.join(data))
        output_stream.write('\n')


if __name__ == '__main__':

    if len(sys.argv) == 1:
        trim_tsv(sys.stdin, sys.stdout)
    elif len(sys.argv) == 2:
        with open(sys.argv[1]) as f:
            trim_tsv(f, sys.stdout)
    else:
        sys.stderr.write("USAGE: trim-tsv [FILE]\n")
        sys.exit(1)
