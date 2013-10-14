% HIGHTLIGHT(1)
% Clark Grubb
% September 12, 2013


# NAME

highlight - highlight text in a stream maching a regular expression

# SYNOPSIS

highlight REGEX [FILE]

highlight (--red|--green|--yellow|--blue|--magenta|--cyan|--white)=REGEX ... [FILE]

highlight (-r|-g|-y|-b|-m|-c|-w)=REGEX ... [FILE]

# DESCRIPTION

Reads lines from file or standard input and writes them to standard out with any
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

-r REGEX, \--red=REGEX
: highlight text matching REGEX in red.

-g REGEX, \--green=REGEX
: highlight text matching REGEX in green.

-y REGEX, \--yellow=REGEX
: highlight text matching REGEX in yellow.

-b REGEX, \--blue=REGEX
: highlight text matching REGEX in blue.

-m REGEX, \--magenta=REGEX
: highlight text matching REGEX in magenta.

-c REGEX, \--cyan=REGEX
: highlight text matching REGEX in cyan.

-w REGEX, \--white=REGEX
: highlight text matching REGEX in white.

\--black=REGEX
: highlight text matching REGEX in black.


# SEE ALSO

`grep` (1)
