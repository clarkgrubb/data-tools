# SUMMARY

A patched version of `mawk` called `tawk` which
by default sets FS and OFS to horizontal tab
(ASCII 9).

# TODO

* FS and OFS default to tab
* error if number of columns not the same (flag to suppress this: -W)
* ability to trim all fields of whitespace (-s)
* use header to create variable names? (-h)
