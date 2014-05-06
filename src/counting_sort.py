#!/usr/bin/env python

import collections
import sys


def usage():
    sys.stderr.write("USAGE: counting-sort [FILE]\n")
    sys.exit(1)


def counting_sort(input_stream, output_stream):
    buckets = collections.defaultdict(int)
    for key in input_stream:
        buckets[key] += 1
    for key in sorted(buckets.keys()):
        for _ in xrange(0, buckets[key]):
            output_stream.write(key)

if __name__ == '__main__':
    if len(sys.argv) == 1:
        counting_sort(sys.stdin, sys.stdout)
    elif len(sys.argv) == 2:
        if sys.argv[1] == '--help':
            usage()
        else:
            with open(sys.argv[1]) as input_stream:
                counting_sort(input_stream, sys.stdout)
    else:
        usage()
