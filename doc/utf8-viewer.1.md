% UTF8-VIEWER(1)
% Clark Grubb
% May 26, 2013


# NAME

utf8-viewer - display Unicode points and optionally names of UTF-8 encoded file

# SYNOPSIS

utf8-viewer [-b|-c|-n] [-w NUM] [FILE]

utf8-viewer [-b|-c|-n] -a BYTE ...

# DESCRIPTION

Convert UTF-8 to Unicode.  The Unicode points are hex digits.  The 
UTF-8 bytes are read from a file, or standard input if no file is specified.
By default eight characters are displayed per line.  The
characters are rendered on the left and the Unicode points are on the right.

With the -a flag each UTF-8 byte is specified as an argument on the
command line. The format of the bytes can be binary,
octal, decimal, or hex.  The prefixes '0b', '0x', and '0' must be
used to indicate binary, hex, and octal bytes, respectively.  Decimal
bytes must not have a leading zero.

# OPTIONS

-a, \--arg
: read the UTF-8 bytes from the command line.  BUG: this flag doesn't work with Ruby 1.8

-b, \--byte-offset
: display the offset in bytes of the leftmost character on the row.

-c, \--char-offset
: display the offset in characters of the leftmost character on the row.

-i, \--invalid-char
: Unicode point of the character to use for invalid bytes.  The default is U+25A0 "BLACK SQUARE".  Has no effect unless the -r flag is also used.

-n, \--name
: use the Internet to lookup the character name for the Unicode code point.  This implies a width of 1.

\--no-render
: don't display the characters in addition to the Unicode points.

-s, \--surrogate-pairs
: show the surrogate pairs that would be used to represent astral code points in UTF-16.

-u, \--unprintable-char
: Unicode point of the character to use for unprintable characters.  The default is U+25A1 "WHITE SQUARE".  Has no effect unless the -r flag is also used.

-w NUM, \--width NUM
: number of characters to display on each row.  Default is 8.

# EXIT STATUS

0
: no invalid UTF-8 byte sequences

1
: invalid command line arguments

2
: invalid UTF-8 byte sequences

# EXAMPLES

How to display the old Mac Roman character set:

    $ ruby -e '(0..255).each { |i| print i.chr }' | iconv -f mac -t utf8 | utf8-viewer

How to display Code Page 437 used by the original IBM PC:

    $ ruby -e '(0..255).each { |i| print i.chr }' | iconv -f cp437 -t utf8 | utf8-viewer

How to display Code Page 1252, also called Windows 1252:

    $ ruby -e '(0..255).each { |i| print i.chr }' | iconv --byte-subst=' ' -f ms-ansi -t utf8 | utf8-viewer

How to display the entire Basic Multilingual Plane:

    $ ruby -e '(0..0xfff).each { |i| print [i].pack("U") }' | utf8-viewer

If you need to convert a Unicode code point to UTF-8 bytes, the following
will work when using the `zsh` shell:

    $ echo -n '\u2028' | od -b

# SEE ALSO

`od` (1), `hexdump` (1), `hexedit` (1)
