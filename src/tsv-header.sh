#!/bin/bash

set -eu -o pipefail

if [ "$#" -gt 1 ]
then
    echo "USAGE: tsv-head PATH" >&2
    exit 1
elif [ "$#" -eq 1 ]
then
    sed -n 1p $1 | tr '\t' '\n' | nl
else
    sed -n 1p | tr '\t' '\n' | nl
fi
