#!/usr/bin/env bash

if [ $# -ne 1 ]
then
    echo "USAGE: $0 INSTALL_DIR" >&2
    exit 1
fi

install_dir=$1

if [ ! -d "$install_dir" ]
then
    echo "ERROR: directory does not exist: $install_dir" >&2
    exit 1
fi

rm -f "$install_dir"/dt
awk '{sub(/ROOT_DIR/, "'"$(pwd)"'", $0); print $0}' < src/dt-uncontained.sh.template > "$install_dir"/dt
chmod +x "$install_dir"/dt
