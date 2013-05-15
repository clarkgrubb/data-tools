% FILE-COUNT-SPLIT(1)
% Clark Grubb
% April 29, 2013


# NAME

file-count-split - split a file into a fixed number of files

# SYNOPSIS

file-count-split -c FILE_COUNT -p PREFIX [-f FILE]

# DESCRIPTION

Split a file into FILE_COUNT files.  The advantage of using
`file-count-split` over `split` is that it is easier to know exactly
how many files will be created.

The suffixes are zero-padded decimal numbers starting from zero.  They
are always padded to the number of digits needed to express FILE_COUNT - 1.

# OPTIONS

-c, \--count
: the number of files to create.

-f, \--file
: the input file.  If not provided, the script reads from stdin.

-p, \--prefix
: the prefix of the output files.

# EXAMPLES

Splits /etc/passwd into the files `/tmp/foo.00`, `/tmp/foo.01`, ...
`/tmp/foo.19`:

    $ file-count-split -c 20 -p /tmp/foo. -f /etc/passwd

# SEE ALSO

`split` (1), `csplit` (1)
