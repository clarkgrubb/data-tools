% SET-DIFF(1)
% Clark Grubb
% May 6, 2013


# NAME

set-diff - find lines in first file which are not in the second

# SYNOPSIS

set-diff FILE1 FILE2

# DESCRIPTION

List the lines which are in the first file and not in the second.

The lines are output in a sorted order and not necessarily the order of the first file.

If the files are already sorted, it is faster to use `comm -23`.  

`comm -23` gives erroneous results with no warning if the input files are not sorted.

# OPTIONS

None

# SEE ALSO

`comm` (1)

`set-intersect` (1)
