#!/usr/bin/env python3
import argparse
import sys
import unicodedata

ENCODING = 'utf-8'
NFC = 'NFC'
NFD = 'NFD'
NFKC = 'NFKC'
NFKD = 'NFKD'


def normalize_utf8(input_stream, output_stream, normalization_form):
    """
    Form must be 'NFC', 'NFD', 'NFKC', or 'NFKC'.

    Normalization forms are explained at

        http://unicode.org/reports/tr15/

    """
    for line in input_stream:
        output_stream.write(unicodedata.normalize(normalization_form, line))


def main():
    parser = argparse.ArgumentParser()
    parser.add_argument('positional_args',
                        nargs='?')
    parser.add_argument('--nfc',
                        action='store_true',
                        dest='nfc')
    parser.add_argument('--nfd',
                        action='store_true',
                        dest='nfd')
    parser.add_argument('--nfkc',
                        action='store_true',
                        dest='nfkc')
    parser.add_argument('--nfkd',
                        action='store_true',
                        dest='nfkd')
    args = parser.parse_args()

    flag_count = 0
    if args.nfc:
        flag_count += 1
        normalization_form = NFC
    if args.nfd:
        flag_count += 1
        normalization_form = NFD
    if args.nfkc:
        flag_count += 1
        normalization_form = NFKC
    if args.nfkd:
        flag_count += 1
        normalization_form = NFKD

    if flag_count == 0:
        args.nfc = True
        normalization_form = NFC
    if flag_count > 1:
        sys.stderr.write('At most one normalization flag can be used.\n')
        parser.print_usage(sys.stderr)
        sys.exit(1)

    if args.positional_args:
        fin = open(args.positional_args, encoding='utf-8')
    else:
        fin = sys.stdin

    normalize_utf8(fin, sys.stdout, normalization_form)


if __name__ == '__main__':
    main()
