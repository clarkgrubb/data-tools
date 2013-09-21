# Introduction

The data-tools repo contains a collection of tools which one engineer has
found to be "missing" from the standard command line environment.

The tools come with man pages which can be installed or browsed on [GitHub](https://github.com/clarkgrubb/data-tools/tree/master/doc).

# Encodings

All tools expect and produce UTF-8 (or 8-bit clean ASCII) encoded data.  Use
`iconv` if you need to deal with a different encoding, e.g:

    iconv -f ISO-8859-1 -t UTF-8 
    iconv -f UTF-8 -t ISO-8859-1
    iconv -l

When a file is in an unknown encoding, one is compelled to inspect it byte-by-byte.
Three tools are suggested.

    od -b
    od -c
    cat -t
    
`od -b` will display the input in octal bytes.  If the file is one of the many 8-bit
extensions of ASCII, `od -c` is useful, since it renders printable ASCII.  `cat -t` will
render ASCII control characters other than LF with ^ notation.  Some versions also use
Emacs style M- notation for upper 8-bit bytes.

    hexedit
    utf8-viewer
   
 How to generate a character given a unicode point
 
 How to lookup a unicode point.

# Newline Delimited Files

The tools use LF as the end-of-line marker in output.  The tools will generally
handle other EOL markers in input correctly.  See [this](http://www.unicode.org/standard/reports/tr13/tr13-5.html)
for a list of the Unicode characters that should be treated as EOL markers.
Use `unix2dos` (see if your package manager has the package `dos2unix`) to convert the output of one of the tools to CRLF style EOL markers.

    tr '\n' '\r'
    tr -d '\r'
    
    dos2unix
    unix2dos
   
Tools are provided for finding the lines which two files share in common, or which are unique to the first file:

    set-intersect FILE1 FILE2
    set-diff FILE1 FILE2
    
The `cat` command can be used to find the union of two files, with an optional `sort -u` to remove duplicate lines:
    
    cat FILE1 FILE2 | sort -u

When inspecting files at the command line, `grep` and `less` are invaluable.  Their man pages reward careful study.
An interesting feature of `grep` is the ability to hightlight the search pattern in red:

    grep --color=always root /etc/passwd
    
The `highlight` command does the same thing, except that it also prints lines which don't match
the pattern.  Also it supports multiple patterns, each with its own color:
    
    highlight --red root --green daemon --blue /bin/bash /etc/passwd

Both `grep` and `highlight` use [ANSI Escape Sequences](http://www.ecma-international.org/publications/standards/Ecma-048.htm).
If you are paging through the output, use `less -R` to render the escape sequences correctly.

 seq
 for
 date-seq

 sort -R | head -10
 awk 'rand() < 0.01'
 sample

# Relational Data Formats

* TSV
* CSV
* XLSX
* JSON

    csv-to-json
    csv-to-tsv
    tsv-to-cvs
    tsv-to-json
    xlsx-to-csv

awk, sort, and join

    head -1 foo.tsv | tr '\t' '\n' | nl

Mongo export format

    tawk
    strip_columns
    header-sort

* csvkit
* sqlite
* importing/exporting from databases

# Hierarchical Data Formats

* JSON
* XML
* HTML
 
    json-awk
    dom-awk
    python -mjson.tool
    xmllint

