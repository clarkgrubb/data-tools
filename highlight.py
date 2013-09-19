#!/usr/bin/env python

import argparse
import re
import sys

NORMAL = '\033[m'
BLACK_FOREGROUND = '\033[01;30m'
RED_FOREGROUND = '\033[01;31m'
GREEN_FOREGROUND = '\033[01;32m'
YELLOW_FOREGROUND = '\033[01;33m'
BLUE_FOREGROUND = '\033[01;34m'
MAGENTA_FOREGROUND = '\033[01;35m'
CYAN_FOREGROUND = '\033[01;36m'
WHITE_FOREGROUND = '\033[01;37m'


def highlight(input_stream, output_stream, esc_seq_to_pattern):
    for line in input_stream:
        output_line = line
        for esc_seq, pattern in esc_seq_to_pattern.iteritems():
            rx = re.compile("({})".format(pattern))
            output_line = rx.sub('{}\\1{}'.format(esc_seq, NORMAL),
                                 output_line)
        output_stream.write(output_line)


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('pattern', nargs='?', metavar='PATTERN')
    parser.add_argument('--black',
                        dest='black',
                        metavar='PATTERN')
    parser.add_argument('--red', '-r',
                        dest='red',
                        metavar='PATTERN')
    parser.add_argument('--green', '-g',
                        dest='green',
                        metavar='PATTERN')
    parser.add_argument('--yellow', '-y',
                        dest='yellow',
                        metavar='PATTERN')
    parser.add_argument('--blue', '-b',
                        dest='blue',
                        metavar='PATTERN')
    parser.add_argument('--magenta', '-m',
                        dest='magenta',
                        metavar='PATTERN')
    parser.add_argument('--cyan', '-c',
                        dest='cyan',
                        metavar='PATTERN')
    parser.add_argument('--white', '-w',
                        dest='white',
                        metavar='PATTERN')

    args = parser.parse_args()

    esc_seq_to_pattern = {}
    if args.pattern and args.red:
        raise Exception('--red|-r cannot be used with default pattern')
    if args.pattern:
        esc_seq_to_pattern[RED_FOREGROUND] = args.pattern
    if args.red:
        esc_seq_to_pattern[RED_FOREGROUND] = args.red
    if args.black:
        esc_seq_to_pattern[BLACK_FOREGROUND] = args.black
    if args.green:
        esc_seq_to_pattern[GREEN_FOREGROUND] = args.green
    if args.yellow:
        esc_seq_to_pattern[YELLOW_FOREGROUND] = args.yellow
    if args.blue:
        esc_seq_to_pattern[BLUE_FOREGROUND] = args.blue
    if args.magenta:
        esc_seq_to_pattern[MAGENTA_FOREGROUND] = args.magenta
    if args.cyan:
        esc_seq_to_pattern[CYAN_FOREGROUND] = args.cyan
    if args.white:
        esc_seq_to_pattern[WHITE_FOREGROUND] = args.white

    if not esc_seq_to_pattern:
        print("No PATTERN specified.")
        parser.print_help()
        sys.exit(1)

    highlight(sys.stdin, sys.stdout, esc_seq_to_pattern)
