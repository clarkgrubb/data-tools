#!/usr/bin/env bash

set -eu -o pipefail

if [ "$#" -lt 2 ]
then
    echo "USAGE: json-diff [DIFF_OPTIONS] PATH1 PATH2" 1>&2
    exit 2
fi

args=("$@")

file1=${args[$(( $# - 2 ))]}
file2=${args[$(( $# - 1 ))]}
unset args[$(( $# - 1 ))]
unset args[$(( $# - 2 ))]
normalized1=$(mktemp)
normalized2=$(mktemp)

function cleanup {
    rm -f "$normalized1" "$normalized2"
}

trap cleanup ERR

function cleanup_and_exit {
    cleanup
    exit "$1"
}

if ! python3 -mjson.tool --sort-keys < "$file1" > "$normalized1"
then
    cleanup_and_exit 2
fi
if ! python3 -mjson.tool --sort-keys < "$file2" > "$normalized2"
then
    cleanup_and_exit 2
fi

set +u
diff "${args[@]}" "$normalized1" "$normalized2"
diff_retval=$?
set -u

cleanup_and_exit "$diff_retval"
