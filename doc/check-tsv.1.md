% CHECK-TSV(1)
% Clark Grubb
% March 6, 2015

# NAME

check-tsv - check whether all rows in a TSV file have the same number of columns

# SYNOPSIS

check-tsv [TSV_FILE]

# DESCRIPTION

Check whether all rows in a TSV file have the same number of columns.

The exit status is 0 if all rows have the same number of fields and 1 if they do not.

For each number of fields the number of rows is printed out.

# OPTIONS

none

# SEE ALSO

`awk` (1), `tawk` (1), `tsv-header` (1), `trim-tsv` (1)
