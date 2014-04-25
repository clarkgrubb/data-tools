#!/bin/bash

set -eu -o pipefail

underscore_url=http://underscorejs.org/underscore.js
if [ -d ~/Local/src ]
then
    underscore_file=~/Local/src/underscore.js
else
    underscore_file=/tmp/underscore.js
fi

if [ ! -e $underscore_file ]
then
  curl $undescore_url > $underscore_file
fi

mongo --shell "$@" $underscore_file
