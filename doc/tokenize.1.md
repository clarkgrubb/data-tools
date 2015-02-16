% TOKENIZE(1)
% Clark Grubb
% February 15, 2105

# NAME

tokenize - extract words from English language text

# SYNOPSIS

tokenize [-n]

# DESCRIPTION

Exract words from English language text.  Words consist of adjacent letters, numbers, and
this punctuation:

    '*+-/=\^_`|~

Control characters and this punctuation delimit words and are removed:

    !#$%&(),:;<>?@[]{}

Space characters also delimit words.  The words are written out separated by spaces unless
the `-n` flag is used, in which case they are separated by newlines.

Non-ASCII characters delimit words and are removed.  It might be desirable to replace accented Latin characters with the unaccented versions.  This command can be used:

    $ iconv -f utf-8 -t ascii//TRANSLIT

# OPTIONS

-n
: write the words out one per line.

# SEE ALSO

`iconv` (1)
