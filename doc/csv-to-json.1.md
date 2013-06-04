% CSV-TO-JSON(1)
% Clark Grubb
% June 4, 2013


# NAME

csv-to-json - convert CSV to JSON

# SYNOPSIS

csv-to-json OPTIONS 

# DESCRIPTION

Read a CSV file from standard input and write the corresponding JSON to standard output.

Each row of the JSON output contains a serialized JSON object.  The values of the object come from the corresponding row of the CSV file, and the header is used fo the keys.

# OPTIONS

-d DELIMITER, \--delimiter=DELIMITER
: Used to read CSV files which use DELIMITER to separate fields instead of a comma.

-q QUOTECHAR, \--quotechar=QUOTECHAR
: Used to read CSV files which use QUOTECHAR to quote fields instead of double quotes.

# SEE ALSO

`tsv-to-json` (1), `json-awk` (1)

http://www.ietf.org/rfc/rfc4180.txt

http://json.org
