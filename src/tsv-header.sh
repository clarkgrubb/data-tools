#!/usr/bin/env bash

set -eu -o pipefail

if [ "$#" -gt 1 ]
then
    echo "USAGE: tsv-head PATH" >&2
    exit 1
elif [ "$#" -eq 1 ]
then
    head -1 "$1" | tr '\t' '\n' | awk '{printf "%6d\t%s\n", NR, $0}'
else
    head -1 | tr '\t' '\n' | awk '{printf "%6d\t%s\n", NR, $0}'
fi
