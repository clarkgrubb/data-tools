% NORMALIZE-UTF8(1)
% Clark Grubb
% February 8, 2014


# NAME

normalize-utf8 - convert UTF-8 encoded files or standard input to a normalized form

# SYNOPSIS

normalize-utf8 [--nfc|--nfd|--nfkc|--nfkd] [FILE]

# DESCRIPTION

Put UTF-8 encoded Unicode text into a normalized form.

Unicode contains different character sequences which are
rendered the same way.  An example is SMALL LETTER C WITH CEDILLA,
which can be represented as a single character: U+00E7 or as SMALL LETTER C
followed by COMBINING CEDILLA: U+0063 U+0327.  When
performing a string comparison, the two sequences should often
be regarded as identifical.  If the strings being compared have
been put into normal form, then a simple string comparison can be
used.

The Unicode standard defines four normalization forms.  NFC (Normal Form C),
which is the default format used by `normalize-utf8`, favors single character
representations over multiple character representations containing
combining marks.  NFC is also called W3C normalization.

Conversely, NFD (Normal Form D) favors multiple character representations
consisting of a simple character representation followed by a combining mark.  Converting
a string to NFD is faster because the algorithm for converting a string to NFC starts by
converting it to NFD.

NFKC and NFKD conflate compatibility composites.  These are sequences which are
visually distinct but semantically the same.  Examples are the ff and ffi ligatures.


# OPTIONS

--nfc
: write input to standard out in Normal Form C

--nfd
: write input to standard out in Normal Form D

--nfkc
: write input to standard out in Normal Form KC

--nfkd
: write input to standard out in Normal Form KD


# SEE ALSO

`utf8-viewer` (1)

http://unicode.org/reports/tr15/

http://www.unicode.org/reports/tr36/
