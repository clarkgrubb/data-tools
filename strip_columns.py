#!/usr/bin/env python

import sys

DELIMITER = '\t'

def strip_columns(input_stream, output_stream):
    for line in input_stream:
        row = line.rstrip('\r\n').split(DELIMITER)
        data = [field.strip() for field in row]
        output_stream.write(DELIMITER.join(data))
        output_stream.write('\n')


if __name__ == '__main__':
    strip_columns(sys.stdin, sys.stdout)
