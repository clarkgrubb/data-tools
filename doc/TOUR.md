[introduction](#intro) | [encodings](#encodings) | [newlines](#newlines) | [relational formats](#relational-fmt) | [hierarchical formats](#hierarchical-fmt)

<a name="intro"/>
# Introduction

The *data tools* come with man pages which can be installed locally or browsed on [GitHub](https://github.com/clarkgrubb/data-tools/tree/master/doc).

The theme of the *data tools* repo is working with data at the command line.  They provide an alternative to importing data into a relational database where it can be manipulated with SQL.  It is an interesting and sometimes useful fact that `awk`, `sort`, and `join` can be used to implement relational algebra.  Still, implementing data workflows at the command line can be frustrated by gaps in the traditional tool set.  The *data tools* repo fills some of those gaps.

Command line tools are composable when the output of one command can be the input of another.  The output can be redirected to a file whose path is passed as an argument, or the commands can be connected by a shell pipe.  Use of pipes is *tacit programming*: it relieves the programmer of the need to name a file.  Furthermore the byte stream is private to the commands on either side of the pipe.   Only tools which read from standard input or write to standard output can participate in a pipeline.

Tools in a pipeline must agree on the *format* of the data in the byte stream.  To promote interoperability, the *data tools*  favor:

* UTF-8 as character encoding (or 8-bit encoded ASCII)
* LF as newline
* TSV format for relational data

When we encounter byte streams in other formats, we invoke *format conversion tools* on them.  The *data tools* repo offers several such tools.

<a name="encodings"/>
# Encodings

[iconv](#iconv) | [bad bytes](#bad-bytes) | [utf-8](#utf-8) | [unicode](#unicode)

<a name="iconv"/>
## iconv

The *data tools* expect and produce UTF-8 encoded data.  Recall that 8-bit encoded ASCII is valid UTF-8.  We can use `iconv` to convert a file in a different encoding:

    $ iconv -t UTF-8 -f UTF-16 /etc/passwd > /tmp/password.utf16
    
To get a list of supported encodings:
    
    $ iconv -l

<a name="bad-bytes"/>
## bad bytes

Not all sequences of bytes are valid UTF-8; the *data tools* with throw exceptions when invalid bytes are encountered.  A drastic way to deal with the problem is to strip the invalid bytes:

    $ iconv -c -f UTF-8 -t UTF-8 < INPUT_FILE > OUTPUT_FILE

Here is how to find non-ASCII bytes:

    grep --color='auto' -P -n "[\x80-\xFF]+"

The `-P` option is not provided by the version of `grep` distributed with Mac OS X.  One can use the `highlight` command in this repo:

    $ highlight '[\x80-\xFF]+'

To find the first occurence of bytes which are not valid UTF-8, use `iconv`:

    $ iconv -f utf-8 -t utf-8 < /bin/ls > /dev/null
    iconv: illegal input sequence at position 24

The *data tool* `utf8-viewer` will render invalid UTF-8 bytes with black squares.  The black square is itself a Unicode character (U+25A0), so there is ambiguity.  The Unicode points are displayed next to the rendered characters, however, and the point will be U+FFFF for invalid characters.

    $ utf8-viewer /bin/ls

When a file is in an unknown encoding, one can inspect it byte-by-byte.
`od -b` displays the bytes in octal:

    $ od -b /bin/ls

`od -b` is an unequivocal way to look at the data.  It removes the confusion caused by the character encoding assumed by the display.  On the other hand it is difficult to make sense of octal bytes.

The *data tools* install a version of the editor [hexedit](http://rigaux.org/hexedit.html) to which a [patch](http://www.volkerschatz.com/unix/hexeditpatch.html) supporting aligned search has been applied.  `F1` for help, `^S` to search, `^X` to exit.  Emacs key bindings can often be used for movement.  `hexedit` displays the bytes in hexadecimal.

If some of the bytes in a file are ASCII, such as when the encoding is one of the many 8-bit extensions of ASCII, then `od -c` will display the file in an unequivocal yet easier-to-interpret way:
    
    $ ruby -e '(0..255).each { |i| print i.chr }' | iconv -f mac -t utf8 | od -c
    
`od -c` uses C backslash sequences or octal bytes for non-ASCII and non-printing ASCII characters.  

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

    echo $'obase=16\n\nibase=8\n42' | bc
    22

<a name="utf-8"/>
## utf-8

The `utf8-viewer` *data tool* provides an easy way to determine the Unicode points of a sequence of UTF-8 bytes.

    $ utf8-viewer foo.txt
   
If you want to see the character for a Unicode point, the following works in `zsh`:

    $ echo $'\u03bb'
     
If you are using a different shell but have access to `python` or `ruby`:
     
    $ python -c 'print(u"\u03bb")'
     
    $ ruby -e 'puts "\u03bb"'
 
<a name="unicode"/>
## unicode

Unicode contains all the characters one is likely to encounter in an encoding system.  It can be difficult to deal with, since it contains characters with strange properties such as combining characters and right-to-left characters.

How to lookup a Unicode point:

    $ curl ftp://ftp.unicode.org/Public/UNIDATA/UnicodeData.txt > /tmp/UnicodeData.txt
    
    $ awk -F';' '$1 == "03BB"' /tmp/UnicodeData.txt 
    03BB;GREEK SMALL LETTER LAMDA;Ll;0;L;;;;;N;GREEK SMALL LETTER LAMBDA;;039B;;039B

`UnicodeData.txt` is a useful file, and possibly it deserves a dedicated path on your file system.  

The first three fields are "Point", "Name", and "[General Category](http://www.unicode.org/reports/tr44/#General_Category_Values)".  

<a name="newlines"/>
# newlines

[eol markers](#eol-markers) | [set operations](#set-op) | [highlighting](#highlighting) | [sequences](#seq) | [sampling](#sampling)

<a name="eol-markers"/>
## eol markers

The *data tools* use LF as the end-of-line marker in output.  The *data tools* will generally
handle other EOL markers in input correctly.  See [this](http://www.unicode.org/standard/reports/tr13/tr13-5.html)
for a list of the Unicode characters that should be treated as EOL markers.
Use `unix2dos` (see if your package manager has the package `dos2unix`) to convert the output of one of the *data tools* to CRLF style EOL markers.

    tr '\n' '\r'
    tr -d '\r'

    dos2unix
    unix2dos
   
<a name="set-op"/>
## set operations

*Data tools* are provided for finding the lines which two files share in common, or which are unique to the first file:

    set-intersect FILE1 FILE2
    set-diff FILE1 FILE2
    
The `cat` command can be used to find the union of two files, with an optional `sort -u` to remove duplicate lines:
    
    cat FILE1 FILE2 | sort -u

<a name="highlighting"/>
## highlighting

When inspecting files at the command line, `grep` and `less` are invaluable.  Their man pages reward careful study.
An interesting feature of `grep` is the ability to hightlight the search pattern in red:

    grep --color=always root /etc/passwd
    
The `highlight` command does the same thing, except that it also prints lines which don't match
the pattern.  Also it supports multiple patterns, each with its own color:
    
    highlight --red root --green daemon --blue /bin/bash /etc/passwd

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

The `seq` is useful in conjunction with the a shell for loop.  This will create a hundred empty files:

    $ for i in $(seq -w 1 100); do touch foo.$i; done

It is also useful to at times to be able to iterate through a sequence of dates.  The *data tools* provide `date-seq` for this.  For example, suppose that you wanted to fetch a set of URLs which contained a date:

    $ for date in $(date-seq --format='%Y/%m/%d' 20130101 20130131)
    > do mkdir -p $date
    > curl "http://blog.foo.com/${date}" > ${date}/index.html
    > done

`date-seq` can iterate though years, months, days, hours, minutes, or seconds.  When iterating through days, the `--weekdays` flag can be used to specify days of the week.  See the [man page](https://github.com/clarkgrubb/data-tools/blob/master/doc/date-seq.1.md) for details.

<a name="sampling"/>
## sampling

It is desirable at times to take a random sample of lines from a file.  Simply taking the first *N* lines is not recommend.  Instead one should shuffle the file first:

    sort -R foo.txt | head -3

On large files, randomly shuffling a file is slow.  Also, the `sort` installed on Mac OS X does not have the `-R` flag.  One can use `awk` to select a random percentage of lines from a file:
    
    awk 'rand() < 0.01' foo.txt
    
This is faster than shuffling the file, but does not produce an accurate sample size, even if you know the number of lines in the file.
    
An efficient and unbiased way to select an exact number of lines from a file is to use reservoir sampling.  The tool `reservoir-sample` implements it:

    $ reservoir-sample --size 3 < /etc/passwd
    
<a name="relational-fmt"/>
# Relational Formats

[tsv](#tsv) | [csv](#csv) | [json](#relational-json) | [xlsx](#xlsx)

As mentioned previously, much that can be done with a SQL SELECT statement in a database can also be done with `awk`, `sort`, and `join`.  If you are not familiar with the commands, consider reading the man pages.

Relational data can be stored in flat files in a variety of ways.  On Unix, the `/etc/passwd` file stores records one per line, with colons (:) separating the seven fields.  We can use `awk` to query the file.

Get the root entry from `/etc/passwd`:

    awk -F: '$1 == "root"' /etc/passwd

Count the number of users by their login shell:

    awk -F: '{cnt[$7] += 1} END {for (sh in cnt) print sh, cnt[sh]}' /etc/passwd

The `/etc/passwd` file format, though venerable, has a bit of an adhoc flavor.  We discuss four widely used formats

<a name="tsv"/>
## tsv

The IANA, which registered MIME types, has a [specification for TSV](http://www.iana.org/assignments/media-types/text/tab-separated-values).  Records are newline delimited and fields are tab-delimited.  There is no mechanism for escaping or quoting tabs and newlines.  Despite this limitation, we prefer to convert the other formats to TSV because `awk`, `sort`, and `join` cannot easily manipulate the other formats.

Tabs receive criticism, and deservedly, because they are indistinguishable as normally rendered from spaces, which can cause cryptic errors.   Trailing spaces in fields can be hidden by tabs, causing joins to mysteriously fail, for example.  `cat -te` can be used to expose trailing spaces.  The `trim-tsv` tool can be used to clean up a TSV file.

The fact that tabs are visually identical to spaces means that in many applications they *can* be replaced by spaces, which makes tabs available for delimiting fields.  One could use a non-printing character, but most applications do not display non-printing characters well.

Here is how to align the columns of a tab delimited file:

    tr ':' '\t' < /etc/passwd | column -t -s $'\t'

The default field separator for `awk` is whitespace.  The correct way to use `awk` on a TSV is like this:

    awk 'BEGIN {FS="\t"; OFS="\t"} ...'

This is an error-prone situation, because sometimes the default behavior works correctly on a TSV file.  Because specifying the field separators is a bit tedious, the repo contains a `tawk` command which uses tabs by default:

    tawk '...'

The IANA spec says that a TSV file must have a header.  Self-describing data is a good practice.  On the other hand the header is at times inconvenient; when sorting the file, for example.  The repo provides the `header-sort` command to sort a file while keeping the header in place.  When we must remove the header, we label the file with a `.tab` suffix instead of a `.tsv` suffix.

Even if a file has a header, `awk` scripts must refer to columns by number instead of name.  The following code displays the header names with their numbers:

    head -1 foo.tsv | tr '\t' '\n' | nl

*generating and parsing TSV with split and join. looping over the fields and outputing a space after each field is a bad practice since it results in an invsible trailing space on the last fields*

<a name="csv"/>
## csv

The CSV format is described in [RFC 4180](http://www.ietf.org/rfc/rfc4180.txt).  

Note that CSV files do not necessarily have headers.  This is perhaps because CSV files are an export format for spreadsheets.

RFC 4180 defines the EOL marker as CRLF.  The *data tools* use LF as the EOL marker, however.  If you want to conform to the spec, run the output through `unix2dos`.  Also note that the final CRLF is optional.

CSV provides a mechanism for quoting commas and EOL markers.  Double quotes are used, and double quotes themselves are escaped by doubling them. 

The *data tools* repo provides utilities for converting between TSV (which can be manipulated by `taw`) and CSV:

    csv-to-tsv
    tsv-to-cvs

Converting from CSV to TSV is problematic if the fields contain tabs or newlines.  By default `csv-to-tsv` will fail if it encounters any.  There are flags to tell `csv-to-tsv` to strip, backslash escape, replace with space, or replace with space and squeeze.   See the [man page](https://github.com/clarkgrubb/data-tools/blob/master/doc/csv-to-tsv.1.md). 

The philosophy of the *data tools* repo is to convert data to TSV. If you would prefer to work with CSV directly, consider downloading [csvkit](http://csvkit.readthedocs.org/en/latest/).

<a name="relational-json"/>
## json

JSON ([json.org](http://json.org/)) is strictly speaking a hierarchical format, but MongoDB uses it for relational (or near relational) data.  The MongoDB export format is a file of serialized JSON objects, one per line.  Whitespace can be added or removed anywhere to a serialized JSON object without changing the data the JSON object represents (except inside strings, and newlines must be escaped in strings).  Thus it is always possible to write a JSON object on a single line.

The following *data tools* are provided to convert CSV or TSV files to the MongoDB export format.  In the case of `csv-to-json`, the CSV file must have a header:

    csv-to-json
    tsv-to-json

`python -mjson.tool` can be used to pretty print JSON and test whether the JSON is well formed.

    $ echo '{"foo":1, "bar": 2, "baz": [1,2,3]}' | python -mjson.tool
    {
        "bar": 2, 
        "baz": [
            1, 
            2, 
            3
        ], 
        "foo": 1
    }

The *data tools* utility `json-awk` can be used to convert JSON to TSV.

    json-awk 'BEGIN{ puts ["foo", "bar", "baz"].join("\t")}; puts [$_["foo"], $_["bar"], $_["baz"]].join("\t")' < dump.json

The script passed to `json-awk` is Ruby.  The JSON is parsed, and the data is stored in the `$_` variable.  If the input is a MongoDB style export with one JSON object per line, then `json-awk` iterates over the file in an awk-like manner, setting the `$_` variable to each object in turn.

<a name="xlsx"/>
## xlsx

XLSX is the default format used by Excel since 2007.  Other spreadsheet applications can read it.

XLSX is a ZIP archive of mostly XML files.  The `unzip -l` command can be used to list the contents of an XLSX file.

Excel provides the ability to export data in a CSV or TSV format.  One exports by choosing the format when saving the workbook.  The CSV formats all use 8-bit encodings and are not recommended since Excel spreadsheets can contain Unicode data.  To export as TSV, look for the "Unicode Text" or "UTF-16 Unicode Text" option.  The file suffix will be `.txt`.  The character encoding is UTF-16 and can be converted using `iconv`:

    iconv -f utf-16 -t utf-8 < foo.txt > foo.tsv

Using Excel to export the data requires having Excel, which is not free.  Also Excel must be run in a desktop environment and is difficult to automate.  The *data tools* include the script `xslx-to-csv` so the operation can be performed at the command line.  To extract the sheets from a workbook as CSV files, run this:

    $ xlsx-to-csv WORKBOOK.xlsx OUTPUT_DIR
    
The directory OUTPUT_DIR will be created and must not already exist.

One can list the sheet names and extract a single sheet to a CSV file:

    $ xlsx-to-csv --list WORKBOOK.xlsx
    
    $ xlsx-to-csv --sheet=SHEET WORKBOOK.xlsx SHEET.csv

By default dates are written in `%Y-%m-%dT%H:%M:%S` format.  This can be change using the `--date-format` flag.  See `man strftime` for instructions on how to specify a date format.

The tool `xls-to-csv` is available for converting the older (pre 2007) Excel spreadsheet to CSV.  It has the same interface as `xlsx-to-csv`.

<a name="hierarchical-fmt"/>
# Hierarchical Formats

Hierarchical data can be stored in JSON, which we discussed above.

## xml and html

To check whether an XML file is wellformed, use

    $ xmllint FILE.xml

The *data tools* include a tool called `dom-awk` for using XPATH or CSS selectors to extract data from an XMl or HTML file.  Here is an example of getting the links from a web page:

    $ curl www.google.com | dom-awk  '$_.xpath("//a").each {|o| puts o["href"] }'

