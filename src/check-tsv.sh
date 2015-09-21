#!/usr/bin/env bash

set -eu -o pipefail

script='BEGIN {FS="\t"; OFS="\t"} {cnt[NF] += 1} END {for (i in cnt) print i, cnt[i]; if (length(cnt) == 1) exit 0; else exit 1}'

if [ "$#" -gt 1 ]
then
    echo "USAGE: tsv-check PATH" >&2
    exit 1
elif [ "$#" -eq 1 ]
then
    awk "$script" "$1"
else
    awk "$script"
fi
