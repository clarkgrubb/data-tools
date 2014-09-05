#!/usr/bin/env bash

if [ $# -eq 0 ]
then
    echo "USAGE: $0 [OPTIONS] FILE"
    exit 1
fi

file="${!#}"

if [ ! -f $file ]
then
    echo "USAGE: $0 [OPTIONS] FILE"
    exit 1
fi

head -1 $file
tail -n +2 $file | sort "${@:1:$(($#-1))}"
