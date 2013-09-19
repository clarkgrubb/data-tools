% HIGHTLIGHT(1)
% Clark Grubb
% September 12, 2013


# NAME

highlight - highlight text in a stream maching a regular expression

# SYNOPSIS

highlight REGEX

highlight (--red|--green|--yellow|--blue|--magenta|--cyan|--white)=REGEX ...

highlight (-r|-g|-y|-b|-m|-c|-w)=REGEX ...

# DESCRIPTION

Reads lines from standard input and writes them to standard out with any
substrings matching REGEX highlighted in red.

This is similar to `grep --color=always REGEX`, but grep will not print
lines which don't match REGEX at all.

The default color is red.  The other choices are green, yellow, blue, magenta,
cyan, white, and black.

Multiple patterns can be specified, but the results when patterns overlap are
unpredictable.

# EXAMPLES

Highlight which shells users are using:

    highlight -r /bin/bash -g /bin/sh -b /usr/bin/zsh -m /bin/false < /etc/passwd

# OPTIONS

None

# SEE ALSO

`grep` (1)
