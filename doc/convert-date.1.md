% CONVERT-DATE(1)
% Clark Grubb
% July 18, 2015

# NAME

convert-date - convert the date format of a column of tab-delimited data

# SYNOPSIS

convert-date [-i FMT] [-o FMT] [-c COLUMN] [-H]

# DESCRIPTION

Convert the dates in a specified column of a tab-delimited file.

By default the first column is processed.  Use the `-c` flag to
specify a different column (the first column is indexed as zero).

If the file has a header, use the `-H` flag to not process it.

Use the `-i` and `-o` flags to set the input and output date formats.

If one of the formats is set to `%s` (i.e. Unix epoch) and the other
format is unspecified, it will be set to `%Y-%m-%dT%H:%M:%S` (ISO 8601 format).

Conversely, if one of the formats is set to `%Y-%m%dT%H:%M:%S` and the
other is unspecified it will be set to `%s`.

# OPTIONS

-c COLUMN
: the column number (zero-based) of the column to convert.

-H / --header
: do not process the first line

-i FMT / --input-format FMT
: the strftime-style format used to parse the input

-o FMT / --output-format FMT
: the stftime-style format used to format the output.

# SEE ALSO

`date` (1), `strftime` (3), `strptime` (3)
