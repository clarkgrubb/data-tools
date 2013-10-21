% JOIN-TSV(1)
% Clark Grubb
% October 21, 2013


# NAME

join-tsv - perform a relation join on two TSV files

# SYNOPSIS

join-tsv --column=NAME [--null=VALUE|--no-null] [--left|--right|--full] TSV\_FILE1 TSV\_FILE2

# DESCRIPTION

Perform a relation join on two TSV files.  The output is written to standard output in TSV format.

`join-tsv` assumes that TSV\_FILE1 and TSV\_FILE2 in accordance with the IANA MIME type specificsation.

`join-tsv` is easier to use than `join` when working with TSV files because it preserves the headers.  It allows specifying the join column by name.

HOW IT IS IMPLEMENTED

HOW NULLS ARE HANDLED

# OPTIONS

-c NAME, \--column=NAME
: Used to read CSV files which use DELIMITER to separate fields instead of a comma.

-f, \--full
: Perform a full outer join.  Rows with a null join value in TSV\_FILE1 or TSV_FILE2 will be included in the output.  

-l, \--left
: Perform a left outer join.  Rows with a null join value in TSV\_FILE1 will be included in the output.

-n=VALUE, \--null=VALUE
: use VALUE as the null value.  The default null value is the empty string.

-N, \--no-null
: no null value.  The empty string can be used as a join value.

-r, \--right
: Perform a right outer join.  Rows with a null join value in TSV\_FILE2 will be included in the output.

# SEE ALSO

`join` (1)

http://www.iana.org/assignments/media-types/text/tab-separated-values
