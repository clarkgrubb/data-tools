#!/bin/sh

if [ $# -lt 1 ]
then
    echo 'IMPLEMENT ME: list of commands' >&2
    exit 0
else
    cmd=shift
    exec $cmd "$@"
fi
