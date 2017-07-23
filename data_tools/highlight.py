#!/usr/bin/env python3

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

BLACK_BACKGROUND = '\033[01;40m'
RED_BACKGROUND = '\033[01;41m'
GREEN_BACKGROUND = '\033[01;42m'
YELLOW_BACKGROUND = '\033[01;43m'
BLUE_BACKGROUND = '\033[01;44m'
MAGENTA_BACKGROUND = '\033[01;45m'
CYAN_BACKGROUND = '\033[01;46m'
WHITE_BACKGROUND = '\033[01;47m'

BOLD = '\033[01;1m'
ITALIC = '\033[01;3m'
UNDERLINE = '\033[01;4m'
INVERT = '\033[01;7m'


def highlight(input_stream, output_stream, esc_seq_to_pattern):
    for line in input_stream:
        output_line = line
        for esc_seq, pattern in esc_seq_to_pattern.items():
            rx = re.compile("({})".format(pattern))
            output_line = rx.sub('{}\\1{}'.format(esc_seq, NORMAL),
                                 output_line)
        output_stream.write(output_line)


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('positional', nargs='*')
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

    parser.add_argument('--black-background',
                        dest='black_background',
                        metavar='PATTERN')
    parser.add_argument('--red-background',
                        dest='red_background',
                        metavar='PATTERN')
    parser.add_argument('--green-background',
                        dest='green_background',
                        metavar='PATTERN')
    parser.add_argument('--yellow-background',
                        dest='yellow_background',
                        metavar='PATTERN')
    parser.add_argument('--blue-background',
                        dest='blue_background',
                        metavar='PATTERN')
    parser.add_argument('--magenta-background',
                        dest='magenta_background',
                        metavar='PATTERN')
    parser.add_argument('--cyan-background',
                        dest='cyan_background',
                        metavar='PATTERN')
    parser.add_argument('--white-background',
                        dest='white_background',
                        metavar='PATTERN')

    parser.add_argument('--normal',
                        dest='normal',
                        metavar='PATTERN')
    parser.add_argument('--bold',
                        dest='bold',
                        metavar='PATTERN')
    parser.add_argument('--italic',
                        dest='italic',
                        metavar='PATTERN')
    parser.add_argument('--underline',
                        dest='underline',
                        metavar='PATTERN')
    parser.add_argument('--invert', '--reverse',
                        dest='invert',
                        metavar='PATTERN')

    args = parser.parse_args()
    pattern = None
    input_path = None

    if len(args.positional) == 1:
        if args.red or args.black or args.green or args.yellow or args.blue \
           or args.magenta or args.cyan or args.white \
           or args.black_background or args.red_background \
           or args.green_background or args.yellow_background \
           or args.blue_background or args.magenta_background \
           or args.cyan_background or args.white_background \
           or args.normal or args.bold or args.italic or args.underline \
           or args.invert:
            input_path = args.positional[0]
        else:
            pattern = args.positional[0]
    elif len(args.positional) == 2:
        pattern, input_path = args.positional
    elif len(args.positional) > 2:
        sys.stderr.write('USAGE: hightlight [OPTIONS] [PATTERN] [FILE]\n')
        sys.exit(1)

    esc_seq_to_pattern = {}
    if pattern and args.red:
        raise Exception('--red|-r cannot be used with default pattern')
    if pattern:
        esc_seq_to_pattern[RED_FOREGROUND] = pattern
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

    if args.black_background:
        esc_seq_to_pattern[BLACK_BACKGROUND] = args.black_background
    if args.red_background:
        esc_seq_to_pattern[RED_BACKGROUND] = args.red_background
    if args.green_background:
        esc_seq_to_pattern[GREEN_BACKGROUND] = args.green_background
    if args.yellow_background:
        esc_seq_to_pattern[YELLOW_BACKGROUND] = args.yellow_background
    if args.blue_background:
        esc_seq_to_pattern[BLUE_BACKGROUND] = args.blue_background
    if args.magenta_background:
        esc_seq_to_pattern[MAGENTA_BACKGROUND] = args.magenta_background
    if args.cyan_background:
        esc_seq_to_pattern[CYAN_BACKGROUND] = args.cyan_background
    if args.white_background:
        esc_seq_to_pattern[WHITE_BACKGROUND] = args.white_background

    if args.normal:
        esc_seq_to_pattern[NORMAL] = args.normal
    if args.bold:
        esc_seq_to_pattern[BOLD] = args.bold
    if args.italic:
        esc_seq_to_pattern[ITALIC] = args.italic
    if args.underline:
        esc_seq_to_pattern[UNDERLINE] = args.underline
    if args.invert:
        esc_seq_to_pattern[INVERT] = args.invert

    if not esc_seq_to_pattern:
        sys.stderr.write("No PATTERN specified.\n")
        parser.print_help()
        sys.exit(1)

    if input_path:
        with open(input_path) as f:
            highlight(f, sys.stdout, esc_seq_to_pattern)
    else:
        highlight(sys.stdin, sys.stdout, esc_seq_to_pattern)


if __name__ == '__main__':
    main()
