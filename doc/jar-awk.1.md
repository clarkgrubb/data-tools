% JAR-AWK(1)
% Clark Grubb
% May 4, 2014


# NAME

jar-awk - read multiline records from a file or standard input and process them with Ruby 

# SYNOPSIS

jar-awk [-t] -l REGEX [-F REGEX] [-b RUBY_SCRIPT] [-e RUBY_SCRIPT] (-f RUBY\_PATH | RUBY\_SCRIPT) [JAR\_INPUT] ...

# DESCRIPTION

`jar-awk` processes multiline records in a file or input stream.  The records are separated by lines which match the REGEX expression specified by the `-l` (`--line-delimiter`) flag.

`jar-awk` processes two formats: `cookie jars` and `record jars`.  These terms from the section on data file formats in the `The Art of Unix Programming`.

In the cookie jar format, the records are just strings of text that can contain new lines.  `jar-awk` sets the variable `$_` to each record in turn.  These cookie jars have nothing to do with browser cookies.

If the `-F` (`--field-delimiter`) flag is used, the input is assumed to be in record jar format.  Each line of the record contains a key-value pair.  The argument of the `-F` flag is a REGEX which is used to split the line in two.  `jar-awk` sets `$_` to a Ruby hash containing the key-value pairs.

The Ruby script can be provided on the command line to do something with `$_` for each record.  Optionally, the `-f` flag can be used to read the Ruby script from a file.

Some cookie jar files and record jar files may put interesting information on the delimiter line.  The match data for the delimiter line is put in the variable `$md`.  If the regular expression contained groups, these are available in `$md[1]`, `$md[2]`, and so on.  The entire matched expression is in `$md[0]`, and what came before and after it is in `$md.pre_match` and `$md.post_match`.

Because `jar-awk` is implemented with `eval` instead of `ruby -e`, `BEGIN` and `END` blocks are not supported.  To specify blocks of Ruby code which execute at the begin and end of execution, use the `-B` (`--BEGIN`) and `-E` (`--END`) flags.

# OPTIONS

-B RUBY\_SCRIPT, \--BEGIN=RUBY\_SCRIPT
: execute Ruby script provided as argument before processing records

-E RUBY\_SCRIPT, \--END=RUBY\_SCRIPT
: execute Ruby script provided as argument after processing records

-f PATH, \--file=PATH
: execute the Ruby script in the file at PATH.

-F REGEX, \--field-delimiter=REGEX
: the regular expression 

-l REGEX, \--line-delimiter=REGEX
: a regular expression for identifying the 

-t, \--trim
: Trim whitespace on the edge of records.  If -F flag is specified, trim whitespace on the edge of keys and values.

# EXAMPLES



# SEE ALSO

`awk` (1)

`csplit` (1)

http://www.catb.org/esr/writings/taoup/html/ch05s02.html
