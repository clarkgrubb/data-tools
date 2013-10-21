[summary](#summary) | [setup](#setup) | [how to run](#how-to-run)

<a name="summary"/>
# SUMMARY

Mostly data extraction and file format conversion tools.  This page describe the tools in brief; the [tour](https://github.com/clarkgrubb/data-tools/blob/master/doc/TOUR.md) describes them in detail.

    csv-to-json        convert CSV to JSON

    csv-to-tsv         convert CSV to TSV

    date-seq           create a sequence of dates

    dom-awk            read HTML or XML into DOM object and process it with Ruby

    header-sort        sort file, keeping header in place

    hexedit            edit a binary file

    highlight          highlight text matching REGEX

    join-tsv           perform a relation join on two TSV files

    json-awk           read JSON objects from standard input and process them with Ruby
    
    reservoir-sample   select N lines from standard input randomly

    set-diff           find lines in first file which are not in the second

    set-intersect      find lines common to two files
    
    tawk               awk, but uses tabs for FS and OFS by default

    trim-tsv           trim whitespace from fields of TSV file
    
    tsv-to-csv         convert TSV to CSV

    tsv-to-json        convert TSV to JSON

    utf8-viewer        display Unicode points and optionally names of UTF-8 encoded file
    
    xls-to-csv         convert XLS to CSV
    
    xlsx-to-csv        convert XLSX to CSV

<a name="setup"/>
# SETUP

To install the necessary Ruby gems and Python packages:

    $ sudo make setup

To put the *data tools* and man pages in your path:

    $ make install

It must be run with permission to create files in the install directory as it creates symlinks to the *data tools* repository.

If you have special installation needs, maybe they are covered [here](https://github.com/clarkgrubb/data-tools/blob/master/doc/INSTALL.md).

<a name="how-to-run"/>
# HOW TO RUN

    csv-to-json        [-d DELIMITER] [-q QUOTECHAR] [CSV_FILE]
    
    csv-to-tsv         [-e|-x|-r[z]] [CSV_FILE]

    date-seq           [--format=FMT] [--weekdays=DAY[,DAY]...] YYYY[MM[DD[HH]]] YYYY[MM[DD[HH]]]

    dom-awk            [-x|-h] (-f SCRIPT_FILE | SCRIPT) [HTML_OR_XML_FILE]

    header-sort        [OPTIONS] FILE

    hexedit            [-m|-s] FILE

    highlight          REGEX [FILE]
    
    highlight          (--red|--green|--yellow|--blue|--magenta|--cyan)=REGEX ... [FILE]

    join-tsv           -c NAME [-l|-r|-f] [-n VALUE] TSV\_FILE1 TSV\_FILE2

    json-awk           [-j|-t] (-f SCRIPT_FILE | SCRIPT) [JSON_FILE] ...

    reservoir-sample   [-r SEED] -s NUM [FILE]

    set-diff           FILE1 FILE2

    set-intersect      FILE1 FILE2

    trim-tsv           [TSV_FILE]

    tsv-to-csv         [-d DELIMITER] [-q QUOTECHAR] [-u] [TSV_FILE]

    tsv-to-json        [TSV_FILE]
    
    utf8-viewer        [-b|-c|-n] [-w NUM] [FILE]

    utf8-viewer        [-b|-c|-n] -a BYTE ...

    xls-to-csv         <same as xlsx-to-csv>

    xlsx-to-csv        [--date-format=DATE_FMT] XLSX_FILE DIRECTORY

    xlsx-to-csv        [--date-format=DATE_FMT] --sheet=SHEET XLSX_FILE [OUTPUT_FILE]
    
    xlsx-to-csv        --list XLSX_FILE
