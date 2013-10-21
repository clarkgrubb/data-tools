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

`join-tsv` is easier to use than `join` when working with TSV files because it preserves the headers.  It allows specifying the join column by name.  If the join column names differ, the column name if the left (i.e. first) file is used in the output.

`join-tsv` performs the join by reading the smaller file into memory.  `join-tsv` can perform left, right, or full outer joins.

The default null value is the empty string.  It is not used as a join value.  It can be changed to something else with the `--null` flag.  The `--no-null` flag can be used to treat all strings including the empty string as join values.

# OPTIONS

-C NAME, \--column=NAME
: the name of the join columns if they are the same.  If they differ, use the -L and -R flags.

-L NAME, \--left-column=NAME
: used to specify the name of the join column in the left (i.e. first) TSV file.

-R, \--right-column
: used to specify the name of the join column in the right (i.e. second) TSV file.

-f, \--full
: Perform a full outer join.  Rows with a null join value in TSV\_FILE1 or TSV_FILE2 will be included in the output.  

-l, \--left
: Perform a left outer join.  Rows with a null join value in TSV\_FILE1 will be included in the output.

-r, \--right
: Perform a right outer join.  Rows with a null join value in TSV\_FILE2 will be included in the output.

-n VALUE, \--null=VALUE
: use VALUE as the null value.  The default null value is the empty string.

-N, \--no-null
: no null value.  The empty string can be used as a join value.

-o, \--outer-null
: the null value used in outer joins.

# SEE ALSO

`join` (1)

http://www.iana.org/assignments/media-types/text/tab-separated-values
