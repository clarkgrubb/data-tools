% SET-INTERSECT(1)
% Clark Grubb
% May 6, 2013


# NAME

set-intersect - find lines common to two files

# SYNOPSIS

set-intersect FILE1 FILE2

# DESCRIPTION

List the lines which are in both the first file and the second file.

If the files are already sorted, it is faster to use `comm -12`.

`comm -12` gives erroneous results with no warning if the input files
are not sorted.

# OPTIONS

None

# SEE ALSO

`comm` (1)

`set-diff` (1)
