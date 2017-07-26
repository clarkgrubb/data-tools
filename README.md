[summary](#summary) | [setup](#setup) | [how to run](#how-to-run)

[.txt](#txt) | [.tsv](#tsv) | [.tab](#tab) | [.csv](#csv) | [.xlsx](#xlsx) | [.json](#json) | [.yaml](#yaml) | [.html](#html) | [.xml](#xml)

[plain text](#plaintext) | [encodings](#encodings) | [newlines](#newlines) | [relational formats](#relational-fmt) | [joins](#joins) | [keys](#keys) | [hierarchical formats](#hierarchical-fmt)

<a name="summary"/>

# SUMMARY

Command line tools for data extraction, data manipulation, and file format conversion.

    check-tsv              verify rows in TSV file are same length

    convert-date           convert dates in tabular data using strftime-style formats

    counting-sort          sort a file using counting sort

    csv-to-json            convert CSV to JSON

    csv-to-postgres        import a CSV file into a PostgreSQL table

    csv-to-tab             convert CSV to tab delimited

    csv-to-xlsx            convert CSV files to XLSX worksheets

    date-fill              fill in missing rows in a TSV file with a time series column

    date-seq               create a sequence of dates

    header-sort            sort file, keeping header in place

    highlight              highlight text matching REGEX

    html-table-to-csv      extract table content from HTML file as CSV

    join-tsv               perform a relation join on two TSV files

    json-pluck             convert JSON array to JSON stream

    json-diff              show differences between two JSON documents

    normalize-utf8         write UTF-8 encoded input to standard out in normalized form

    postgres-to-csv        write a PostgreSQL table to stdout in CSV format

    reservoir-sample       select N lines from standard input randomly

    set-diff               find lines in first file which are not in the second

    set-intersect          find lines common to two files

    tab-to-csv             convert tab delimited file to CSV

    tokenize               extract words from English language text

    trim-tsv               trim whitespace from fields of TSV file

    tsv-header             show TSV header with ordinal position of each column

    tsv-to-json            convert TSV to JSON

    utf8-category          tally UTF-8 encoded characters by general category

    utf8-script            tally UTF-8 encoded characters by script

    utf8-viewer            display Unicode points and optionally names of UTF-8 encoded file

    xls-to-csv             convert XLS to CSV

    xlsx-to-csv            convert XLSX to CSV

    yaml-to-json           convert YAML to JSON



The *data tools* are for working with data at the command line.  They are meant to complement the tools you already have.  Use `help SUBCOMMAND` to see the help page for a *data tool* or browse the help pages on [GitHub](https://github.com/clarkgrubb/data-tools/tree/master/doc).

Command line tools are composable when the output of one command can be the input of another.  The output can be redirected to a file whose path is passed as an argument, or the commands can be connected by a shell pipe.  Use of a pipe is *tacit programming*: it relieves the programmer of the need to name a file.  Furthermore the byte stream is private to the commands on either side of the pipe.  

Only tools which read from standard input or write to standard output can participate in a pipeline.  Tools in a pipeline must agree on the *format* of the data in the byte stream.  The *data tools* support these formats: `.txt`, `.tsv`, `.tab`, `.csv`, `.xls`, `.xlsx`, `.json`, `.yaml`, `.html`, and `.xml`.  Some of the *data tools* are *format conversion tools* to be used to convert from one format to another.

<a name="setup"/>

# SETUP

`python3`, `pip3` and `gcc` are required.

To install Python and Bash scripts:

    $ ./setup.py sdist
    $ pip3 install dist/data-tools-0.1.0.tar.gz

To install C tools:

    $ make install.c

To install man pages:

    $ make install.man

<a name="how-to-run"/>

# HOW TO RUN

    check-tsv              [TSV_FILE]

    convert-date           [-i FMT] [-o FMT] [-c COLUMN] [-H]

    counting-sort          [FILE]

    csv-to-json            [-d DELIMITER] [-q QUOTECHAR] [CSV_FILE]

    csv-to-postgres        -f CSV_PATH -t TABLE [-d DB] [-h HOST] [-p PORT] [-U USER] [-w|-W]

    csv-to-tab             [-e|-x|-r] [CSV_FILE]

    csv-to-xlsx            -o XLSX_FILE CSV_FILE ...

    date-fill              --date-column NUM --format FORMAT

    date-seq               [--format=FMT] [--weekdays=DAY[,DAY]...] YYYY[MM[DD[HH]]] YYYY[MM[DD[HH]]]

    header-sort            [OPTIONS] FILE

    highlight              REGEX [FILE]

    highlight              (--red|--green|--yellow|--blue|--magenta|--cyan)=REGEX ... [FILE]

    html-table-to-csv      [-t TABLE_NUM] [FILE]

    join-tsv               -c NAME [-l|-r|-f] [-n VALUE] TSV_FILE1 TSV_FILE2

    json-pluck             < FILE

    json-diff              [DIFF_OPTIONS] JSON_FILE1 JSON_FILE2

    normalize-utf8         [--nfc|--nfd|--nfkc|--nfkd] [FILE]

    postgres-to-csv        -t TABLE [-d DB] [-h HOST] [-p PORT] [-U USER] [-w|-W]

    reservoir-sample       [-r SEED] -s NUM [FILE]

    set-diff               FILE1 FILE2

    set-intersect          FILE1 FILE2

    tab-to-csv             [-u] [TAB_DELIMITED_FILE]

    tokenize               [-n]

    trim-tsv               [TSV_FILE]

    tsv-header             [TSV_FILE]

    tsv-to-json            [TSV_FILE]

    utf8-category          [-l|--long-names] [-c|--count-ascii|-s|--skip-ascii]

    utf8-script            [-c|--count-ascii|-s|--skip-ascii]

    utf8-viewer            [-b|-c|-n] [-w NUM] [FILE]

    utf8-viewer            [-b|-c|-n] -a BYTE ...

    xls-to-csv             <same as xlsx-to-csv>

    xlsx-to-csv            [--date-format=DATE_FMT] XLSX_FILE DIRECTORY

    xlsx-to-csv            [--date-format=DATE_FMT] --sheet=SHEET XLSX_FILE [OUTPUT_FILE]

    xlsx-to-csv            --list XLSX_FILE

    yaml-to-json           [FILE]

<a name="plaintext"/><a name="txt"/>

# PLAIN TEXT: .TXT

*Plain text* is a sequence of bytes which use an encoding to represent printable characters.

If no other suffix is appropriate, `.txt` is a reasonable suffix for a plain text file.

In plain text, control characters other than for line endings and perhaps tabs are disallowed.  Long lines are discouraged.

<a name="encodings"/>

# ENCODINGS

[iconv](#iconv) | [bad bytes](#bad-bytes) | [utf-8](#utf-8) | [utf-16](#utf-16) | [unicode](#unicode)

<a name="iconv"/>

## iconv

The *data tools* expect and produce UTF-8 encoded data.  8-bit encoded ASCII is valid UTF-8.

Use `iconv` to convert a file in a different encoding:

    $ iconv -t UTF-8 -f UTF-16 foo.utf16.txt > foo.utf8.txt

To get a list of supported encodings:

    $ iconv -l

<a name="bad-bytes"/>

## bad bytes

Not all sequences of bytes are valid UTF-8; the *data tools* throw exceptions when invalid bytes are encountered.  A drastic way to deal with the problem is to strip the invalid bytes:

    $ iconv -c -f UTF-8 -t UTF-8 < INPUT_FILE > OUTPUT_FILE

This command strips all non-ASCII characters:

    $ iconv -c -f UTF-8 -t ASCII < INPUT_FILE > OUTPUT_FILE

One can try to transliterate the non-ASCII characters:

    $ iconv -f UTF-8 -t ASCII//TRANSLIT < INPUT_FILE > OUTPUT_FILE

Here is a way to find non-ASCII bytes:

    $ grep --color='auto' -P -n "[\x80-\xFF]+"

The `-P` option is not provided by the version of `grep` distributed with Mac OS X.  One can use the `highlight` command in this repo:

    $ highlight '[\x80-\xFF]+'

To find the first occurrence of bytes which are not valid UTF-8, use `iconv`:

    $ iconv -f utf-8 -t utf-8 < /bin/ls > /dev/null
    iconv: illegal input sequence at position 24

`utf8-viewer` will render invalid UTF-8 bytes with black squares.  The black square is itself a Unicode character (U+25A0), so there is ambiguity.  The Unicode points are displayed next to the rendered characters, however, and the point will be ---- for invalid characters.

    $ utf8-viewer /bin/ls

When a file is in an unknown encoding, one can inspect it byte-by-byte.
`od -b` displays the bytes in octal:

    $ od -b /bin/ls

`od -b` is an unequivocal way to look at the data.  It removes the confusion caused by the character encoding assumed by the display.  On the other hand it is difficult to make sense of octal bytes.

If some of the bytes in a file are ASCII, such as when the encoding is one of the many 8-bit extensions of ASCII, then `od -c` will display the file in an unequivocal yet easier-to-interpret way:
    
    $ ruby -e '(0..255).each { |i| print i.chr }' | iconv -f mac -t utf8 | od -c
    
`od -c` uses C backslash sequences or octal bytes for non-ASCII and non-printing ASCII characters.  

`xxd` displays the data in rows of 16 bytes.  Each row is displayed in 3 columns.  The first column is the hex offset of the first byte in the row, the second column is the bytes in hex, and third column is the ASCII characters for the bytes, with a period `.` standing in for control characters and upper 8-bit bytes.  The `-c` flag changes the number of bytes per row:

    $ xxd /bin/ls
    $ xxd -c 32 /bin/ls
    
The `-i` flag will convert the data to a C source literal.  The `-r` flag will convert the output of `xxd` back to the original binary format:
    
    $ xxd -i /bin/ls
    $ xxd /bin/ls | xxd -r

The `-s` flag and the `-l` flag specify the start byte and the total number of bytes to display:

    $ xxd -s 10 -l 20 /bin/ls

Another way to pick out bytes from a file is `dd`:

    $ dd bs=1 iseek=10 count=20 if=/etc/passwd 2> /dev/null

`cat -te` uses a unique escape sequence for each byte, but unlike `od`, it does not display
a fixed number of bytes per line; the mapping from input to output is not injective.  Still, since it doesn't introduce line breaks at regular intervals, it may be easier to interpret.  An example:

    $ ruby -e '(0..255).each { |i| print i.chr }' | iconv -f mac -t utf8  | cat -te

`cat -t` renders printable ASCII and newlines; it uses `^` notation for other control characters.  Some versions of `cat -t`
use Emacs style `M-X` notation for upper 8-bit bytes.  In this case, `X` will be what `cat -t` would have used to render
the character if the upper bit were zero, with the exception of `^J` being used for newline.

The Ruby interpreter can be pressed into service as a tool for performing base conversion:

    $ ruby -e 'puts "316".to_i(8).to_s(16)'
    ce

The `bc` calculator can also be used:

    $ echo $'obase=16\n\nibase=8\n316' | bc
    CE

<a name="utf-8"/>

## utf-8

The `utf8-viewer` *data tool* provides an easy way to determine the Unicode points of a sequence of UTF-8 bytes.

    $ utf8-viewer foo.txt
   
If you want to see the character for a Unicode point, use `printf`:

    $ printf '\u03bb\n'
    
`zsh` and recent versions of `bash` honor the `\u` backslash escape sequence in `$' '` strings:

    $ echo $'\u03bb'
     
If you have access to `python` or `ruby`:
     
    $ python -c 'print(u"\u03bb")'
     
    $ ruby -e 'puts "\u03bb"'
 
The *data tools* provide `utf8-category` and `utf8-script`, which summarize the characters by general category and script:
 
    echo 'It is greater than ∞!' | utf8-category -l
    1	Control
    14	Lowercase_Letter
    1	Uppercase_Letter
    5	Other_Punctuation
    1	Math_Symbol
 
    $ echo 'αλφα βητα foo bar' | utf8-script
    4	Common
    8	Greek
    6	Latin
 
Both tools have `-c` and `-s` flags for counting ASCII characters separately or omitting them from the tally entirely.
 
<a name="utf-16"/>

## utf-16

Unicode points above `U+FFFF` are represented in UTF-16 by a pair of 16-bit characters called _surrogates_:

    $ echo -n 𝒷 | iconv -f utf-8 -t utf-16 | xxd
    0000000: feff d835 dcb7

The first 16-bit character is the byte order mark (BOM).  The second 16-bit character is the _high surrogate_, and the third 16-bit character is the _low surrogate_.  A high surrogate is in the range  0xD800 to 0xDBFF, and a low surrogate is in the range 0xDC00 to 0xDFFF.

In some programming languages, one must use surrogates to insert a point from the supplementary planes in a string literal:

    $ scala
    scala> "\ud835\udcb7"
    res0: String = 𝒷

Here is Python code describing the conversion from surrogates to code point and back:

    def to_high_and_low_surrogate(n):
        assert(0xFFFF < n <= 0x10FFFF)
        high = 0xD800 + (((n - 0x10000) >> 10) & 0x3FF)
        low = 0xDC00 + ((n - 0x10000) & 0x3FF)
        return high, low
    
    def to_code_point(high, low):
        assert(0xD800 <= high < 0xDC00)
        assert(0xDC00 <= low <= 0xDFFF)
        return (high - 0xD800) * 0x400 + (low - 0xDC00) + 0x10000

<a name="unicode"/>

## unicode

How to look up a Unicode point:

    $ curl ftp://ftp.unicode.org/Public/UNIDATA/UnicodeData.txt > /tmp/UnicodeData.txt
    
    $ awk -F';' '$1 == "03BB"' /tmp/UnicodeData.txt 
    03BB;GREEK SMALL LETTER LAMDA;Ll;0;L;;;;;N;GREEK SMALL LETTER LAMBDA;;039B;;039B

`UnicodeData.txt` is a useful file and possibly deserves a dedicated path on the file system.

The first three fields are "Point", "Name", and "[General Category](http://www.unicode.org/reports/tr44/#General_Category_Values)".  

Unicode contains all the characters one is likely to need, but writing code which handles the entire Unicode character
set correctly is sometimes impractical.  One might opt to reject characters which are not needed instead.  A character
frequency table such as used when breaking ciphers is useful in this context:

    $ cat /etc/passwd |  ruby -ne '$_.split("").each { |ch| puts "#{ch} #{ch.ord}" }' | sort | uniq -c | sort -nr


Unicode contains different character sequences which are
rendered the same way.  An example is SMALL LETTER C WITH CEDILLA `ç`,
which can be represented as a single character: U+00E7 or as SMALL LETTER C
followed by COMBINING CEDILLA: U+0063 U+0327.

When performing a string comparison, the two sequences should often
be regarded as identifical.  The easiest way to accomplish this is to put
the strings to be compared into a normalized form.  The Unicode standard defines
[four normal forms](http://unicode.org/reports/tr15/).  The *data tool* `normalize-utf8` can be used to put a UTF-8 encoded file or stream into any of them.

<a name="newlines"/>

# NEWLINES

[eol markers](#eol-markers) | [set operations](#set-op) | [highlighting](#highlighting) | [sequences](#seq) | [sampling](#sampling)

<a name="eol-markers"/>

## eol markers

The *data tools* interpret LF, CRLF, or CR as end-of-line markers in input.  The *data tools* use LF as the end-of-line marker in output.  To convert LF line endings to CRLF or CR line endings:

    $sed 's/$'"/$(echo \\\r)/"
    
    $ tr '\n' '\r'

To convert CRLF or CR line endings to LF line endings:

    $ tr -d '\r'
    
    $ tr '\r' '\n'

For LF to CRLF conversions, another option is the following tools (which might need to be installed, see if your package manager has `dos2unix`).  These tools take paths as arguments and modify the files in place:

    dos2unix
    unix2dos
   
The Unicode Consortium provides a [complete list](http://www.unicode.org/standard/reports/tr13/tr13-5.html) of Unicode characters that might be treated as EOL markers.  In a line-delimited file format these characters should be escaped or removed.

The terminal wraps long lines without any indication that it has done so.  The `cut` command and the environment variable `COLUMNS` can be used to truncate long lines instead:

    $ cut -c 1-$COLUMNS FILE
    $ cut -c $(( $COLUMNS + 1 ))-$(( 2 * $COLUMNS )) FILE

<a name="set-op"/>

## set operations

*Data tools* are provided for finding the lines which two files share in common, or which are exclusive to the first file:

    $ set-intersect FILE1 FILE2
    $ set-diff FILE1 FILE2
    
The `cat` command can be used to find the union of two files, with an optional `sort -u` to remove duplicate lines:
    
    $ cat FILE1 FILE2 | sort -u

<a name="highlighting"/>

## highlighting

When inspecting files at the command line, `grep` and `less` are invaluable.  `grep` can highlight the search pattern in red:

    $ grep --color=always root /etc/passwd
    
The `highlight` command does the same thing, except that it also prints lines which don't match
the pattern.  Also it supports multiple patterns, each with its own color:
    
    $ highlight --red root --green daemon --blue /bin/bash /etc/passwd

Both `grep` and `highlight` use [ANSI Escapes](http://www.ecma-international.org/publications/standards/Ecma-048.htm).  If you are paging through the output, use `less -R` to render the escape sequences correctly.

<a name="seq"/>

## sequences

The `seq` command can generate a newline delimited arithmetic sequence:

    $ seq 1 3
    1
    2
    3

Zero-padded:

    $ seq -w 08 11
    08
    09
    10
    11
    
Step values other than one:

    $ seq 1 .5 2
    1
    1.5
    2

The `seq` is useful in conjunction with a shell `for` loop.  This will create a hundred empty files:

    $ for i in $(seq -w 1 100); do touch foo.$i; done

It is also useful at times to be able to iterate through a sequence of dates.  The *data tools* provide `date-seq` for this.  For example, suppose that you wanted to fetch a set of URLs which contained a date:

    $ for date in $(date-seq --format='%Y/%m/%d' 20130101 20130131)
    > do mkdir -p $date
    > curl "http://blog.foo.com/${date}" > ${date}/index.html
    > done

`date-seq` can iterate though years, months, days, hours, minutes, or seconds.  When iterating through days, the `--weekdays` flag can be used to specify days of the week.  See the [man page](https://github.com/clarkgrubb/data-tools/blob/master/doc/date-seq.1.md) for details.

<a name="sampling"/>

## sampling

It is desirable at times to take a random sample of lines from a file.  Simply taking the first *N* lines often does not yield a representative sample.  Instead one should shuffle the file first:

    $ sort -R foo.txt | head -3

On large files, randomly shuffling a file is slow.  Also, the `sort` installed on Mac OS X does not have the `-R` flag.  One can use `awk` to select a random percentage of lines from a file:
    
    $ awk 'rand() < 0.01' foo.txt
    
This is faster than shuffling the file, but does not produce a precise sample size, even if you know the number of lines in the file.
    
An efficient and unbiased way to select an exact number of lines from a file is to use reservoir sampling.  The *data tool* `reservoir-sample` implements it:

    $ reservoir-sample --size 3 < /etc/passwd

# TSV, TAB, CSV, and XLSX

<a name="relational-fmt"/>

# RELATIONAL FORMATS

[tsv](#tsv) | [csv](#csv) | [xlsx](#xlsx)

Much that can be done with a SQL SELECT statement in a database can also be done with `awk`, `sort`, and `join`.

Relational data can be stored in flat files in a variety of ways.  On Unix, the `/etc/passwd` file stores records one per line, with colons (:) separating the seven fields.  We can use `awk` to query the file.

Get the root entry from `/etc/passwd`:

    $ awk -F: '$1 == "root"' /etc/passwd

Count the number of users by their login shell:

    $ awk -F: '{cnt[$7] += 1} END {for (sh in cnt) print sh, cnt[sh]}' /etc/passwd

The `/etc/passwd` file format, though venerable, has an ad hoc flavor.  In the following sections we consider three formats which are widely used for relational data.

<a name="tsv"/>

## tsv

The IANA, which is responsible for registering MIME types, has a [specification for TSV](http://www.iana.org/assignments/media-types/text/tab-separated-values).  Records are newline delimited and fields are tab-delimited.  There is no mechanism for escaping or quoting tabs and newlines.  Despite this limitation, we prefer to convert the other formats to TSV because `awk`, `sort`, and `join` cannot easily manipulate the other formats.  By default Hadoop uses tabs as a field separator.

Trailing spaces in fields can be hidden by tabs, causing joins to mysteriously fail.  `cat -te` can be used to expose trailing spaces.  The *data tool* `trim-tsv` can be used to clean up a TSV file.

The fact that tabs are visually identical to spaces means that in many applications they *can* be replaced by spaces.  This makes tabs available for delimiting fields.  One could use a non-printing character, but most applications do not display non-printing characters well: inspecting the data is harder.

Here is how to align the columns of a tab delimited file:

    $ tr ':' '\t' < /etc/passwd | column -t -s $'\t'

The default field separator for `awk` is whitespace.  The correct way to use `awk` on a TSV is like this:

    $ awk 'BEGIN {FS="\t"; OFS="\t"} ...'

The IANA spec says that a TSV file must have a header.  Self-describing data is a good practice.  On the other hand the header is at times inconvenient—when sorting the file, for example.  The repo provides the `header-sort` command to sort a file while keeping the header in place.  When we must remove the header, we label the file with a `.tab` suffix instead of a `.tsv` suffix.

Even if a file has a header, `awk` scripts must refer to columns by number instead of name.  The following code displays the header names with their numbers:

    $ head -1 foo.tsv | tr '\t' '\n' | nl

Python and similar languages have a `split` method which is ideal for parsing a TSV file:

    with open(path) as f:
        header = f.readline().rstrip('\r\n').split('\t')
        for line in f:
            fields = line.rstrip('\r\n').split('\t')
                ...

CSV libraries are sometimes used to read TSV files.  This works when the delimiter can be changed from a comma to a tab.  The practice is incorrect if the library does not also allow the quote character to be set to none.

The `join` method in Python and similar languages can be used to generate a TSV file.  Remember to check for prohibited characters in the data:

    import re
    
    RX_PROHIBITED = re.compile(u'[\f\n\r\t\v\x85\u2028\u2029]')
    
    def tsv_replace(field, replace_char=' '):
        return RX_PROHIBITED.sub(replace_char, field)

    with open(path, 'w') as f:
        for row in rows:
            f.write(u'\t'.join([tsv_replace(field) for field in row]))
            f.write(u'\n')

<a name="csv"/>

## csv

The CSV format is described in [RFC 4180](http://www.ietf.org/rfc/rfc4180.txt).  

Note that CSV files do not necessarily have headers.  This is perhaps because CSV files are an export format for spreadsheets.

RFC 4180 defines the EOL marker as CRLF.  The *data tools* use LF as the EOL marker, however.  If you want to conform to the spec, run the output through `unix2dos`.  Also note that the final CRLF is optional.

CSV provides a mechanism for quoting commas and EOL markers.  Double quotes are used, and double quotes themselves are escaped by doubling them. 

The *data tools* repo provides utilities for converting between TSV and CSV:

    csv-to-tab
    tab-to-csv

Converting from CSV to TSV is problematic if the fields contain tabs or newlines.  By default `csv-to-tab` will fail if it encounters any.  There are flags to tell `csv-to-tab` to strip, backslash escape, replace with space, or replace with space and squeeze.   See the [man page](https://github.com/clarkgrubb/data-tools/blob/master/doc/csv-to-tab.1.md). 

<a name="xlsx"/>

## xlsx

XLSX is the default format used by Excel since 2007.  Other spreadsheet applications can read it.

XLSX is a ZIP archive of mostly XML files.  The `unzip -l` command can be used to list the contents of an XLSX file.

Excel provides the ability to export data in a CSV or TSV format.  One exports by choosing the format when saving the workbook.  The CSV formats all use 8-bit encodings and are not recommended since Excel spreadsheets can contain Unicode data.  To export as TSV, look for the "Unicode Text" or "UTF-16 Unicode Text" option.  The file suffix will be `.txt`.  The character encoding is UTF-16 and can be converted using `iconv`:

    $ iconv -f utf-16 -t utf-8 < foo.txt > foo.tsv

Using Excel to export the data requires having Excel, which is not free.  Also Excel must be run in a desktop environment and is difficult to automate.  The *data tools* include the script `xslx-to-csv` so the operation can be performed at the command line.  To extract the sheets from a workbook as CSV files, run this:

    $ xlsx-to-csv WORKBOOK.xlsx OUTPUT_DIR
    
The directory OUTPUT_DIR will be created and must not already exist.

One can list the sheet names and extract a single sheet to a CSV file:

    $ xlsx-to-csv --list WORKBOOK.xlsx
    
    $ xlsx-to-csv --sheet=SHEET WORKBOOK.xlsx SHEET.csv

By default dates are written in `%Y-%m-%dT%H:%M:%S` format.  This can be change using the `--date-format` flag.  See `man strftime` for instructions on how to specify a date format.

The tool `xls-to-csv` is available for converting the older (pre 2007) Excel spreadsheet to CSV.  It has the same interface as `xlsx-to-csv`.

The tool `csv-to-xlsx` is available for creating XLSX workbooks.  Each CSV file on the command line becomes a worksheet in the workbook.  The worksheet names are derived from the CSV file names; see the man page for details.

Importing UTF-8 encoded data into Excel is not effortless. What I have found to work is to convert the data to a tab delimited `.tab` format, but change the suffix to `.txt` since otherwise Excel will not allow the path to be selected.  Then use `File | Import...` and select `Text file`.  After the file path is selected, Excel drops the user into a wizard which allows the format of the file to be specified. The default file origin on Macintosh is `Macintosh`, which is an 8-bit encoding.  Change it to `Unicode (UTF-8)`.  Select `Delimited`.  One the second screen, set `Delimiters` to `Tab`, and `Text qualifier`, which controls to quote character, to `{none}`.  The optional third screen allows the user to set the date formats of the columns.

<a name="joins"/>

# JOINS

[tab](#join-tab) | [tsv](#join-tsv) | [sqlite](#sqlite) | [postgres](#postgres) | [r](#join-r) | [pandas](#join-pandas) | [hive](#hive) | [spark](#spark)

<a name="join-tab"/>

## tab

To illustrate joining at the command line we create some tab delimited files:

    $ grep -v '^#' /etc/passwd | tr ':' '\t' > /tmp/pw.tab
    
    $ grep -v '^#' /etc/group | tr ':' '\t' > /tmp/grp.tab

Here is an example of using `sort` and `join` to join by group id:

    $ sort -t $'\t' -k 4,4 /tmp/pw.tab > /tmp/pw.sort.tab
    
    $ sort -t $'\t' -k 3,3 /tmp/grp.tab > /tmp/grp.sort.tab

    $ join -t $'\t' -1 4 -2 3 /tmp/pw.sort.tab /tmp/grp.sort.tab

This is tedious because (1) each file must be sorted by the join column, (2) the field delimiter must be specified for each invocation of `sort` and `join`, and (3) the join column index must be determined and specified.

<a name="join-tsv"/>

## tsv

`sort` and `join` don't handle files with headers correctly.  Since TSV files have headers, the *data tools* include a `join-tsv` command.

To illustrate using `join-tsv` let's create some TSV files:

    $ ( echo $'name\tpw\tuid\tgid\tgecos\thome\tshell';  grep -v '^#' /etc/passwd | tr ':' '\t' ) > /tmp/pw.tsv
    
    $ ( echo $'name\tpw\tgid\tlist';  grep -v '^#' /etc/group | tr ':' '\t' ) > /tmp/grp.tsv

If the join column has the same name in both files, it can be specified with the `-c` or `--column` flag:

    $ join-tsv --column=gid /tmp/pw.tsv /tmp/grp.tsv

The output is in TSV format, and in particular it has a header.  The order of columns is (1) join column, (2) left file columns other than the join column, (3) right file columns other than the join column.  If the join column has different names in the two files, the left name is used in the output.

`join-tsv` reads the smaller of the two files into memory.

`join-tsv` treats an empty string as the null value by default.  It can perform left, right, or full outer joins.  See the  [man page](https://github.com/clarkgrubb/data-tools/blob/master/doc/join-tsv.1.md) for details.
 
<a name="sqlite"/>

## sqlite

Using SQLite to perform a join:

    $ sqlite3
    
    > create table pw ( name text, pw text, uid int, gid int, gecos text, home text, shell text );
    > create table grp ( name text, pw text, gid int, list text );
    > .separator \t
    > .import /tmp/pw.tab pw
    > .import /tmp/grp.tab grp
    > .mode csv
    > .output /tmp/pw_grp.csv
    > select * from pw join grp on pw.gid = grp.gid;

There is no way to escape the separator when importing files into SQLite.

<a name="postgres"/>

## postgres

    $ tab-to-csv < /tmp/pw.tab > /tmp/pw.csv
    $ tab-to-csv < /tmp/grp.tab > /tmp/grp.csv
    
    $ psql
    > create table pw ( name text, pw text, uid int, gid int, gecos text, home text, shell text );
    > create table grp ( name text, pw text, gid int, list text );
    
    $ ( echo 'copy pw from stdin with (format csv); '; cat /tmp/pw.csv ) | psql
    $ ( echo 'copy grp from stdin with (format csv); '; cat /tmp/grp.csv ) | psql
    
    $ psql
    > create table pw_grp as select pw.name as pw_name, grp.name as grp_name from pw join grp on pw.gid = grp.gid;
    
    $ echo 'copy pw_grp to stdout with (format csv);' | psql > /tmp/pw_grp.csv

<a name="join-r"/>

## r

Using R to perform a join:

    $ /usr/bin/r
    
    > pw = read.delim('/tmp/pw.tsv', quote='')
    
    > grp = read.delim('/tmp/grp.tsv', quote='')

    > j = merge(pw, grp, by.x='gid', by.y='gid')

    > write.table(j, '/tmp/pw_grp.tsv', row.names=F, sep='\t', quote=F)

<a name="join-pandas"/>

## pandas

Using the Python library *pandas* to perform a join:

    $ python
    
    > import pandas as pd
    
    > pw = pd.read_table('/tmp/pw.tsv')
    
    > grp = pd.read_table('/tmp/grp.tsv')
    
    > j = pd.merge(pw, grp, left_on='gid', right_on='gid')
    
    > j.to_csv('/tmp/pw_grp.tsv', sep='\t', index=False)

<a name="hive"/>

## hive

[Hive functions](https://cwiki.apache.org/confluence/display/Hive/LanguageManual+UDF#LanguageManualUDF-explode)

The native format of Hive is to use `^A` (`%x01`) as field delimiters and newlines as row delimiters.

    $ hive -hiveconf mapred.job.tracker=local -hiveconf fs.default.name=file:///tmp -hiveconf hive.metastore.warehouse.dir=file:///tmp/test_hive
    
    > create table passwd ( user string, passwd string, uid int, gid int, gecos string, home string, shell string ) row format delimited fields terminated by '\t' stored as textfile;
    > load data local inpath '/tmp/pw.tab' overwrite into table passwd;
    > create table group ( group string, passwd string, gid int, members string ) row format delimited fields terminated by '\t' stored as textfile;
    > load data local inpath '/tmp/grp.tab' overwrite into table group;
    > insert overwrite local directory '/tmp/pw_grp' row format delimited fields terminated by '\t' select * from passwd p join group g on p.gid = g.gid;

Suppose that we have data in a file which is not in first normal form.  Here the 4th column contains the name of the children, separated by pipes:

    $ cat /tmp/families.tab
    Simpson	Homer	Marge	Bart|Lisa|Maggie
    Cleaver	Ward	June	Wally|Beaver

We can use Hive to normalize the data:

    > create table families (surname string, father string, mother string, children string) row format delimited fields terminated by '\t' stored as textfile;
    > load data local inpath '/tmp/families.tab' overwrite into table families;
    > create table families2 as select surname, father, mother, split(children, '\\|') as children from families;
    > select surname, father, mother, child from families2 lateral view explode(children) foo as child;

The result is the table:

    Simpson	Homer	Marge	Bart
    Simpson	Homer	Marge	Lisa
    Simpson	Homer	Marge	Maggie
    Cleaver	Ward	June	Wally
    Cleaver	Ward	June	Beaver

<a name="spark"/>

## spark

    $ spark-shell
    > val pw = sc.textFile("/etc/passwd").filter(line => line(0) != '#').map(line => line.split(":"))
    > val grp = sc.textFile("/etc/group").filter(line => line(0) != '#').map(line => line.split(":"))
    > val j = pw_gid.join(grp_gid).map(tup => List(tup._1) ++ tup._2._1 ++ tup._2._1)
    > j.map(row => row.mkString("\t")).saveAsTextFile("/tmp/pw_grp")
    
<a name="keys"/>

# KEYS

A *candidate key* is a minimal set of columns which can be used to uniquely identify rows.  A primary key is a candidate key, and other candidate keys can be declared using a uniqueness constraint.  When a candidate key is declared the database rejects inserts and updates that would violate the uniqueness constraint.

Candidate keys are a property of the data; they aren't necessarily declared in the schema.  To verify a candidate key, one checks whether the number of rows in table is the same as the number of distinct values of a column or a set of columns:

    > SELECT COUNT(*) FROM customers;
    > SELECT COUNT(DISTINCT name) FROM customers;
    > SELECT COUNT(*) FROM (SELECT DISTNCT first_name, last_name FROM customers);

Strictly speaking, one should also verify that no proper subset of the columns is also a candidate key.

Usually a join condition is a test of equality between one or more columns from the left relation and the same number of columns from the right relation.

    > SELECT c.name, sum(o.amount) FROM customers c JOIN orders o ON c.id = o.customer_id GROUP BY c.name;

Usually, the columns should be a candidate key for either the left or the right relation.  Consider the following perverse query:
    
    > SELECT c.name, sum(o.amount) FROM customers c JOIN orders o ON c.name = o.customer_name GROUP BY c.name;

If there were _n_ customers with the same name, then the amount associated with their common name would be _n times_ the sum of their orders.  Incidentally, keeping the name of the customer in the orders relation is a violation of second normal form if a unique identifier for the customer is already in the orders table.

<a name="hierarchical-fmt"/>

# HIERARCHICAL FORMATS

[json](#json) | [yaml](#yaml) | [html](#html) | [xml](#xml)

<a name="json"/>

## json

[json.org](http://json.org/)

The MongoDB export format is a file of serialized JSON objects, one per line.  Whitespace can be added or removed anywhere to a serialized JSON object without changing the data the JSON object represents (except inside strings, and newlines must be escaped in strings).  Thus it is always possible to write a JSON object on a single line.

It is easier for most clients to process a large data set in the MongoDB export format, e.g.

    {"foo": 1}
    {"bar": 2}
    {"baz": 3}
    ...
    
than to process a large JSON array, e.g.

    [{"foo":1},{"bar":2},{"baz":3},...]
    
This is because the latter format forces most clients to read the entire data set into memory.  The *data tools* repo contains a utility for dealing with a large JSON array:

    json-pluck < big_array.json > mongo_format.json

The following *data tools* are provided to convert CSV or TSV files to the MongoDB export format.  In the case of `csv-to-json`, the CSV file must have a header:

    csv-to-json
    tsv-to-json

`python -mjson.tool` can be used to pretty print JSON and test whether the JSON is well formed.

    $ echo '{"foo": 1, "bar": 2, "baz": [1, 2, 3]}' | python -mjson.tool
    {
        "bar": 2,
        "baz": [
            1,
            2,
            3
        ],
        "foo": 1
    }

Other tools for pretty printing JSON are `jq` and `json` which can be installed using the operating system package manager and `npm`, respectively:

    $ echo '{"foo": 1, "bar": 2, "baz": [1, 2, 3]}' | jq '.'

    $ echo '{"foo": 1, "bar": 2, "baz": [1, 2, 3]}' | json

The `json-diff` script uses `python -mjson.tool` and `diff` to compare two JSON documents.

The *data tools* utility `json-ruby` can be used to convert JSON to TSV.

    $ json-ruby 'BEGIN{ puts ["foo", "bar", "baz"].join("\t")}; puts [$_["foo"], $_["bar"], $_["baz"]].join("\t")' < dump.json

The script passed to `json-ruby` is Ruby.  The JSON is parsed, and the data is stored in the `$_` variable.  If the input is a MongoDB style export with one JSON object per line, then `json-ruby` iterates over the file in an awk-like manner, setting the `$_` variable to each object in turn.

An alternative to `python -mjson.tool` and `json-ruby` is the `node` based `json` command line tool:

    $ npm install json

    $ echo '{"foo": 1, "bar": 2, "baz": [1,2,3]}' | json

There are some practices which producers of JSON should follow to reduce the complexity of the client.

When processing JSON, a first task might be to determine what the top level keys in each object are: 

    $ cat foo.json | json-ruby 'puts $_.keys.join("\n")' | sort | uniq -c

This code assumes that the top level keys don't contain newlines.  One could check whether this is true:

    $ cat foo.json | json-ruby 'puts $_.keys.select {|k| /\n/.match(k)}'

The value associated with each key can be null, boolean, numeric, string, array, or JSON object.  The value associated with a key should have a consistent type in all of the data.  As a point of style, rather than having a key with a null value, consider omitting the key entirely.

This code lists the top level keys and their values:

    $ cat foo.json | json-ruby 'puts $_.keys.map {|k| k + " " + $_[k].class.to_s}.join("\n")' | sort | uniq -c

If any key has a JSON object as a value, then the above analysis must be repeated.  Note that such data can be flattened:

    {
      "name": "John Smith",
      "address": {
        "street": "123 Main",
        "city": "Jamestown",
        "state": "VA"
      }
    }

can be replaced with:

    {
      "name": "John Smith",
      "address.street": "123 Main",
      "address.city": "Jamestown",
      "address.state": "VA"
    }

Use plural names for keys when the values are arrays.  The values in an array should have the same type.  One can imagine using an array as a shortcut for a JSON object, e.g.:

    ["123 Main", "Jamestown", "VA"]
    
for
    
    {"street": "123 Main", "city": "Jamestown", "state": "VA"}
    
This forces the client to determine the meaning of the positions and hard code those positions in code.

<a name="yaml"/>

## yaml

To process YAML, convert it to JSON and use tools such as `json-ruby`, `jq` and `json`:

    $ yaml-to-json .travis.yml | jq '.script'

This can also be used to verify that YAML is valid.

<a name="html"/>

## html

TODO: a replacement for `dom-ruby`.

To extract the content of an HTML table from an HTML document:

    $ curl 'http://hyperpolyglot.org/scripting' | html-table-to-csv -t 0

The `-t` flag specifies which table to extract. By default the first table, numbered 0, is extracted.

<a name="xml"/>

## xml

To check whether an XML file is well-formed, use:

    $ xmllint FILE.xml

To pretty-print XML:

    $ xmllint --format FILE.xml

XML has some advantages over JSON.  One is XPATH, which can be used to extract data from deep within a document.

Another advantage is schemas.  However, the move from DTDs to XML schemas means one must deal with namespaces, which are complicated.  Libraries such as `libxml2` don't implement namespaces completely.

XML provides two different ways for representing relational data:

    <address street="123 Main" city="Jamestown" state="MA"/>
    
    <address>
      <street>123 Main</street>
      <city>Jamestown</city>
      <state>MA</state>
    </address>
