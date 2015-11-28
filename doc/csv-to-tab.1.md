% CSV-TO-TAB(1)
% Clark Grubb
% February 16, 2013


# NAME

csv-to-tab - convert CSV to tab delimited

# SYNOPSIS

csv-to-tab OPTIONS [CSV_FILE]

# DESCRIPTION

Read a CSV file from file specified on command line or standard input and write the corresponding tab delimited file to standard output.

In the tab delimited format fields are delimited by tabs and records are terminated by an end-of-line marker.  `csv-to-tab` uses newline as the end-of-line marker.

There is no mechanism for quoting tabs or newlines, and by default `csv-to-tab` will fail if they occur in the fields of the CSV file.  

# OPTIONS

-e, \--escape
: Use backslash escape sequences to escape tabs, carriage returns, newlines, and backslashes.

-r, \--replace
: replaces tabs and characters that should be interpreted as newlines as newlines with spaces.  The characters treated as newlines are: \\f \\n \\r \\v \\x85 \\u2028 \\u2029.

-x, \--strip
: Remove tabs, carriage returns, and newlines in fields.


# SEE ALSO

`tab-to-csv` (1)

http://www.ietf.org/rfc/rfc4180.txt

http://www.iana.org/assignments/media-types/text/tab-separated-values
