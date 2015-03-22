% POSTGRES-TO-CSV(1)
% Clark Grubb
% March 21, 2015

# NAME

postgres-to-csv - export a PostgreSQL table to a CSV file

# SYNOPSIS

postgres-to-csv -t TABLE [-d DB] [-h HOST] [-p PORT] [-U USER] [-w|-W]

# DESCRIPTION

Write a PostgreSQL table to standard out in CSV format.

All options other than `-t` are passed to `psql`.

The `PGPASSWORD` environment variable can be used to pass the PostgreSQL
password to `psql`.

# OPTIONS

-d DB
: name of the PostgreSQL database

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

`csv-to-postgres` (1)
