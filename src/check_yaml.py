#!/usr/bin/env python

import sys
import yaml

try:
    if (len(sys.argv) > 2):
        sys.stderr.write("USAGE: check-yaml [FILE]")
    elif (len(sys.argv) == 2):
        with open(sys.argv[1]) as f:
            print(yaml.safe_dump(yaml.safe_load(f.read())))
    else:
        print(yaml.safe_dump(yaml.safe_load(sys.stdin.read())))
except yaml.scanner.ScannerError as e:
    sys.stderr.write(str(e))
    sys.exit(1)
