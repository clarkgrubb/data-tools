% COUNTING-SORT(1)
% Clark Grubb
% May 6, 2014

# NAME

counting-sort - perform counting sort on a file or standard input

# SYNOPSIS

counting-sort [FILE]

# DESCRIPTION

Counting sort is fast when the number of distinct values is small
compared to the total number of values.  For example, when sorting
a file with 3M rows but only 300 distinct values, the regular `sort`
takes 2m30s whereas `counting-sort` only takes 3s.

`counting-sort` only does a lexical sort.

# OPTIONS

None

# SEE ALSO

`sort` (1)

http://en.wikipedia.org/wiki/Counting_sort

