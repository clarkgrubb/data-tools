#!/bin/bash

if [ $# -eq 0 ]
then
    echo "USAGE: head-sort [OPTIONS] FILE"
    exit 1
fi

file="${!#}"

if [ ! -f $file ]
then
    echo "USAGE: head-sort [OPTIONS] FILE"
    exit 1
fi

head -1 $file
tail -n +2 $file | sort "${@:1:$(($#-1))}"
