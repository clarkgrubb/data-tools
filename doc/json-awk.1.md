% JSON-AWK(1)
% Clark Grubb
% February 17, 2013


# NAME

json-awk - read JSON objects from standard input and process them with Ruby 

# SYNOPSIS

json-awk [-j|-t] RUBY_SCRIPT 

# DESCRIPTION

Read JSON from standard input, parse it, and call the Ruby script provided on the command line on the result.  The parsed JSON object is placed in the global accumulator variable $_.

JSON cannot contain newlines.  Hence if the input contains newlines, each line is assumed to contain a single JSON object and the Ruby script is invoked after each line is parsed.  BEGIN and END blocks can be defined in the manner of `awk` to define Ruby code which executes at the start or end of execution.
     
# OPTIONS

-j, \--json
: after the Ruby script is executed, write the contents of $_ to standard output as JSON.

-t, \--tsv
: after the Ruby script is executed, write the contents of $_, which is expected to be an Array, to standard output in tab separated values format.

# SEE ALSO

`awk` (1)

http://json.org/