#!/usr/bin/env bash

set -eu -o pipefail

if [ "$#" -gt 1 ]
then
    echo "USAGE: tsv-head PATH" >&2
    exit 1
elif [ "$#" -eq 1 ]
then
    head -1 "$1" | tr '\t' '\n' | nl
else
    head -1 | tr '\t' '\n' | nl
fi
