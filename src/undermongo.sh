#!/bin/bash

set -eu -o pipefail

readonly underscore_url=http://underscorejs.org/underscore.js
if [ -d ~/Local/src ]
then
    underscore_file=~/Local/src/underscore.js
    cleanup_underscore_file=0
else
    # Can't use mktemp. :(
    # File must have .js suffix.
    underscore_file=/tmp/underscore.$$.js
    rm -f $underscore_file
    cleanup_underscore_file=1
fi

if [ ! -e $underscore_file ]
then
  curl -s $underscore_url > $underscore_file
fi

mongo --shell "$@" $underscore_file

if [ $cleanup_underscore_file ]
then
    rm -f $underscore_file
fi
