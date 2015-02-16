#!/usr/bin/env bash

if [ \( "$#" -eq 1 \) -a \( "$1" = "-n" \) ]
then
    tr -C '0-9a-zA-Z\047\052\053\055\057\075\134\136\137\140\174\176' ' ' | tr -s ' ' | tr ' ' '\n'
elif [ "$#" -eq 0 ]
then
    tr -C '0-9a-zA-Z\047\052\053\055\057\075\134\136\137\140\174\176' ' ' | tr -s ' '
else
    echo "USAGE: tokenize [-n]" 1>&2
    exit 1
fi
