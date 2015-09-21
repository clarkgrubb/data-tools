#!/usr/bin/env bash

set -eu -o pipefail

psql=psql
table=

while getopts "d:h:p:t:U:wW" opt
do
    case "$opt" in
        d) psql="$psql -d $OPTARG" ;;
        h) psql="$psql -h $OPTARG" ;;
        p) psql="$psql -p $OPTARG" ;;
        t) table="$OPTARG" ;;
        U) psql="$psql -U $OPTARG" ;;
        w) psql="$psql -w" ;;
        W) psql="$psql -W" ;;
        ?) table='' ; break ;;
    esac
done

if [ -z "$table" ]
then
    echo "USAGE: postgres-to-csv -t TABLE" >&2
    echo >&2
    echo "  Flags passed to psql:" >&2
    echo "    [-d DB] [-h HOST] [-p PORT] [-U USER] [-w|-W]" >&2
    echo >&2
    echo "  Environment variable PGPASSWORD can be used to set password." >&2
    echo >&2
    exit 1
fi

echo 'copy '"$table"' to stdout with (format csv);' | $psql
