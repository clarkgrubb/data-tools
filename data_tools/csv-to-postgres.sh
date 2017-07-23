#!/usr/bin/env bash

set -eu -o pipefail

psql=psql
table=
path=

while getopts "d:f:h:p:t:U:wW" opt
do
    case "$opt" in
        d) psql="$psql -d $OPTARG" ;;
        f) path="$OPTARG" ;;
        h) psql="$psql -h $OPTARG" ;;
        p) psql="$psql -p $OPTARG" ;;
        t) table="$OPTARG" ;;
        U) psql="$psql -U $OPTARG" ;;
        w) psql="$psql -w" ;;
        W) psql="$psql -W" ;;
        ?) table='' ; break ;;
    esac
done

if [ -z "$table" ] || [ -z "$path" ]
then
    echo "USAGE: csv-to-postgres -f CSV_PATH -t TABLE" >&2
    echo >&2
    echo "  Flags passed to psql:" >&2
    echo "    [-d DB] [-h HOST] [-p PORT] [-U USER] [-w|-W]" >&2
    echo >&2
    echo "  Environment variable PGPASSWORD can be used to set password." >&2
    echo >&2
    exit 1
fi

( echo 'copy '"$table"' from stdin with (format csv); '; cat "$path" ) | $psql
