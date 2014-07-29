#!/bin/bash

set -eu -o pipefail

# TODO: pass options to diff
# TODO: option to pipe to colordiff

if [ "$#" -ne 2 ]
then
    echo "USAGE: json-diff PATH1 PATH2" 1>&2
    exit 2
fi

normalized1=$(mktemp /tmp/json-diff-XXXXX)
normalized2=$(mktemp /tmp/json-diff-XXXXX)

function cleanup {
    rm -f $normalized1 $normalized2
}

trap cleanup ERR

function cleanup_and_exit {
    cleanup
    exit $1
}

if ! python -mjson.tool < $1 > $normalized1
then
    cleanup_and_exit 2
fi
if ! python -mjson.tool < $2 > $normalized2
then
    cleanup_and_exit 2
fi

diff $normalized1 $normalized2
cleanup_and_exit $?
