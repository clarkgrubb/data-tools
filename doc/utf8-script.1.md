% UTF8-SCRIPT(1)
% Clark Grubb
% February 14, 2015


# NAME

utf8-script - tally characters by UTF-8 script 

# SYNOPSIS

utf8-script [-c|\--count-ascii|-s|\--skip-ascii]

# DESCRIPTION

Tally the characters in the standard input stream by UTF-8 script.

# OPTIONS

-c, \--count-ascii
: treat ASCII characters as a separate script called "ASCII".

-s, \--skip-ascii
: skip ASCII characters.  Only characters with Unicode point U+0080 and higher are counted.

# SEE ALSO

http://unicode.org/Public/UNIDATA/Scripts.txt

