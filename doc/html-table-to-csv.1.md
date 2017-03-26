% HTML-TABLE-TO-CSV(1)
% Clark Grubb
% March 26, 2017


# NAME

html-table-to-csv - convert CSV to JSON

# SYNOPSIS

html-table-to-csv [-t TABLE\_NUM] [HTML_FILE]

# DESCRIPTION

Read a HTML file from file specified on command line or standard input, extract the contents of a table in the document, and write the corresponding CSV to standard output.

# OPTIONS

-t TABLE\_NUM, \--table=TABLE\_NUM
: Used to specify which table to extract from the HTML document. By default the first table, numbered 0, is extracted.

# SEE ALSO

http://www.ietf.org/rfc/rfc4180.txt

