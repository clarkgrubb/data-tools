# OVERVIEW

Convert a UTF-8 encoded TSV file to a UTF-8 encoded CSV file.

# DATA DEFINITIONS

TSV format: [IANA](https://www.iana.org/assignments/media-types/text/tab-separated-values).

CSV format: [RFC 4180](https://tools.ietf.org/html/rfc4180).

One goal of this code is to never produce invalid input.  That is, the output should always be in CSV format.

According to RFC 4180, CSV files use CRLF for EOL.

If a field contains comma, CR, LF, or double quote ", it must be quoted.  Double quotes are escaped by doubling them.

If the field does not contain these characters, then quoting is optional.  The easiest implementation would quote all fields. However, this expands the file size, and is undesirable for numeric columns.

Thus, we adopt we scan each field to see whether it has characters which require quoting.  This means we must pass over the data twice.  However, we don't want to dynamically allocate any memory, so if the field exceeds the size of our buffer we quote it.

Our buffer scheme is as follows.  We read pages of bytes in size 4096.  We alternately read pages into two buffers.  If a field is longer than our page size, we quote it.  The two buffers guarantee that we can always back up at least 4096 characters when we find the end of the field, unless it exceeds our limit, in which case we quote it.

# CHARACTER ENCODING

The data standards we follow don't specify the character encoding.  We use UTF-8.  Use `iconv` or some other conversion tool to convert to this format.

*Error handling when not UTF-8?*

# FLAGS

    -u --unescape

