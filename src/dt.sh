#!/bin/sh

if [ $# -lt 1 ]
then
    echo 'USAGE: dt SUBCOMMAND [ARGS] ...' >&2
    echo '' >&2
    echo 'subcommands:' >&2
    ( cd bin && ls ) >&2
    exit 0
else
    cmd=$1
    shift
    exec ./bin/$cmd "$@"
fi
