% HIGHTLIGHT(1)
% Clark Grubb
% September 12, 2013


# NAME

highlight - highlight text in a stream maching a regular expression

# SYNOPSIS

highlight REGEX

# DESCRIPTION

Reads lines from standard input and writes them to standard out with any
substrings matching REGEX highlighted in red.

This is similar to `grep --color=always REGEX`, but grep will not print
lines which don't match REGEX at all.

# OPTIONS

None

# SEE ALSO

`grep` (1)
