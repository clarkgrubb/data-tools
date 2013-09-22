% TSV-TO-CSV(1)
% Clark Grubb
% February 16, 2013


# NAME

tsv-to-csv - convert TSV to CSV

# SYNOPSIS

tsv-to-csv OPTIONS [TSV_FILE]

# DESCRIPTION

Read a TSV file from file specified on the command line or standard input and write the corresponding CSV file to standard output.

In the TSV format fields are delimited by tabs and records are terminated by an end-of-line marker.

There is no mechanism for quoting tabs or newlines, and by default `csv-to-tsv` will fail if they occur in the fields of the CSV file.  

# OPTIONS

-d DELIMITER, \--delimiter=DELIMITER
: Used to read CSV files which use DELIMITER to separate fields instead of a comma.

-q QUOTECHAR, \--quotechar=QUOTECHAR
: Used to read CSV files which use QUOTECHAR to quote fields instead of double quotes.

-u, \--unescape
: Interpret the following backslash sequences when encountered in the data: \n, \r, \t, \\.


# SEE ALSO

`csv-to-tsv` (1)

http://www.ietf.org/rfc/rfc4180.txt

http://www.iana.org/assignments/media-types/text/tab-separated-values
