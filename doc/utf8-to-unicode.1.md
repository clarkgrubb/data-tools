% UTF8-TO-UNICODE(1)
% Clark Grubb
% April 3, 2013


# NAME

utf8-to-unicode - convert UTF-8 bytes to Unicode code point

# SYNOPSIS

utf8-to-unicode [-n|\--name] BYTE ...

# DESCRIPTION

Convert UTF-8 to Unicode.  The UTF-8 is passed as individual
bytes on the command line.  The format of the bytes can be binary,
octal, decimal, or hex.  The prefixes '0b', '0x', and '0' must be
used to indicate binary, hex, and octal bytes, respectively.

# OPTIONS

-n, \--name
: use the Internet to lookup the character name for the Unicode code point.

# EXAMPLES

Both invocations return U+2028:

    $ utf8-to-unicode 0342 0200 0250

    $ utf8-to-unicode.rb 226 128 168

If you need to convert a Unicode code point to UTF-8 bytes, the following
will work when using the `zsh` shell:

    $ echo -n '\u2028' | od -b

# SEE ALSO

`od` (1), `hexdump` (1)
