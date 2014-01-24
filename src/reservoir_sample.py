#!/usr/bin/env python

import argparse
import random
import sys


def reservoir_sample(count, input_stream, output_stream):

    n = None
    output = []

    try:
        n = int(count)
        if n < 1:
            raise ValueError
    except ValueError:
        raise Exception('argument not a positive integer')

    for i, line in enumerate(input_stream):
        if i < n:
            output.append(line)
        else:
            choice = random.randint(0, i)
            if choice < n:
                output[choice] = line

    for line in output:
        output_stream.write(line)


if __name__ == '__main__':

    parser = argparse.ArgumentParser()
    parser.add_argument('positional',
                        nargs='?',
                        metavar='FILE')
    parser.add_argument('--size', '-s',
                        dest='size',
                        type=int,
                        metavar='NUM',
                        required=True)
    parser.add_argument('--random-seed', '-r',
                        dest='random_seed',
                        default=None)
    args = parser.parse_args()

    if args.random_seed:
        random.seed(args.random_seed)

    if args.positional:
        with open(args.positional) as f:
            reservoir_sample(args.size, f, sys.stdout)
    else:
        reservoir_sample(args.size, sys.stdin, sys.stdout)
