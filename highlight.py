#!/usr/bin/env python

import re
import sys


def highlight(input_stream, output_stream, pattern):
    rx = re.compile("({})".format(pattern))
    for line in input_stream:
        output_stream.write(rx.sub('\033[01;31m\033[K\\1\033[m\033[K', line))


if __name__ == '__main__':
    if len(sys.argv) != 2:
        raise Exception("USAGE: highlight.y PATTERN")
    highlight(sys.stdin, sys.stdout, sys.argv[1])
