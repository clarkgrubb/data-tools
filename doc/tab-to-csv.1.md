% TAB-TO-CSV(1)
% Clark Grubb
% February 16, 2013


# NAME

tab-to-csv - convert tab delimited to CSV

# SYNOPSIS

tab-to-csv OPTIONS [TSV_FILE]

# DESCRIPTION

Read a tab delimited file from file specified on the command line or standard input and write the corresponding CSV file to standard output.

In the tab delimited format fields are delimited by tabs and records are terminated by an end-of-line marker.

# OPTIONS

-u, \--unescape
: Interpret the following backslash sequences when encountered in the data: \n, \r, \t, \\.

# SEE ALSO

`csv-to-tab` (1)

http://www.ietf.org/rfc/rfc4180.txt

http://www.iana.org/assignments/media-types/text/tab-separated-values
