% CSV-TO-POSTGRES(1)
% Clark Grubb
% March 21, 2015

# NAME

csv-to-postgres - import a CSV file to a PostgreSQL table

# SYNOPSIS

csv-to-postgres -f CSV_PATH -t TABLE [-d DB] [-h HOST] [-p PORT] [-U USER] [-w|-W]

# DESCRIPTION

Import a CSV file into a PostgreSQL table.

The table is not emptied before the new rows are imported.

All options other than `-t` and `-f` are passed to `psql`.

The `PGPASSWORD` environment variable can be used to pass the PostgreSQL
password to `psql`.

# OPTIONS

-d DB
: name of the PostgreSQL database

-f PATH
: path of the CSV file

-h HOST
: PostgreSQL server host

-p PORT
: the port number.

-t TABLE
: the name of the PostgreSQL table to export

-U USER
: the PostgreSQL user to connect as

-w
: do not prompt for PostgreSQL password

-W
: prompt for PostgreSQL password


# SEE ALSO

`postgres-to-csv` (1)
