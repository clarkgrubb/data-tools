#!/bin/bash

if [ $# -ne 2 ]
then
    echo "USAGE: set-intersect FILE1 FILE2"
    exit 1
fi

sorted1=$(mktemp /tmp/set-diff-XXXXX)
sorted2=$(mktemp /tmp/set-diff-XXXXX)

sort -u $1 > $sorted1
sort -u $2 > $sorted2
cat $sorted1 $sorted2 | sort | uniq -d
rm $sorted1 $sorted2
