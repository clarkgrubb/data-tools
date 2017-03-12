#!/bin/sh

if [ $# -lt 1 ]
then
    echo 'IMPLEMENT ME: list of commands' >&2
    exit 0
else
    cmd=$1
    shift
    exec ./bin/$cmd "$@"
fi
