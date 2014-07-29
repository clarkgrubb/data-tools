% JSON-DIFF(1)
% Clark Grubb
% July 29, 2014


# NAME

json-diff - run diff on two JSON documents

# SYNOPSIS

json-diff [DIFF_OPTIONS] PATH1 PATH2

# DESCRIPTION

Run `diff` on two JSON documents.  Each document is normalized using `python -mjson.tool`.

# OPTIONS

Any options are passed to `diff`.

# SEE ALSO

`diff` (1)
