% TSV-TO-JSON(1)
% Clark Grubb
% June 4, 2013


# NAME

tsv-to-json - convert TSV to JSON

# SYNOPSIS

tsv-to-json OPTIONS [TSV_FILE]

# DESCRIPTION

Read a TSV file from file specified on the command line or standard input and write the corresponding JSON to standard output.

Each row of the JSON output contains a serialized JSON object.  The values of the object come from the corresponding row of the CSV file, and the header is used fo the keys.

# OPTIONS

None

# SEE ALSO

`csv-to-json` (1), `json-awk` (1)

http://www.iana.org/assignments/media-types/text/tab-separated-values

http://json.org
