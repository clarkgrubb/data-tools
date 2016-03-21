# OVERVIEW

Convert a UTF-8 encoded CSV file to a UTF-8 encoded tab delimited file.

# DATA DEFINITIONS

CSV format: [RFC 4180](https://tools.ietf.org/html/rfc4180).

TSV format: [IANA](https://www.iana.org/assignments/media-types/text/tab-separated-values).

TAB format: same as the TSV format, except that the header is optional.

The TSV format requires a header, but the CSV format does not.  It is difficult for a program to verify that a header is present, hence the name `csv-to-tab` instead of `csv-to-tab`.

Another requirement of a TSV file is for each row to have the same number of fields.  This is also a requirement of a CSV.  The command does not check this.

CSV files are supposed to use CRLF to terminate records.  As a convenience, the code will also accept a document which uses LF to terminate records, or even a mix of CRLF and LF.  The code does not accept CR as a record terminator, even though some CSV producers--e.g. Excel on Mac--produce this format.  Accepting a mix of CRLF, LF, and CR would make the number of line endings ambiguous.  Use `sed` to convert such a file.

The TSV format does not specify the exact format of the EOL.  We use LF.

The TSV format cannot include tabs or EOL.  To be safe, we prohibit any character that might be interpreted as an EOL according to the Unicode consortium.  The default behavior is to fail.  Options are provided to strip, backslash escape, or replace with a space character.

# CHARACTER ENCODING

The data standards we follow don't specify the character encoding.  We use UTF-8.  Use `iconv` to convert from another encoding.

# FLAGS

    -x --strip
    -r --replace
    -e --escape

# STATE MACHINE

This describes the state transitions of the C code in the default mode; i.e. when no flags are set.

<img src="state.png">

# TODO

* Enforce that each row has same number of fields. (optional flag?)
* Restore -p N/--pad=N parameter.
