
# SUMMARY

File format conversion tools.

    csv-to-json        convert CSV to JSON

    csv-to-tsv         convert CSV to TSV

    date-seq           create a sequence of dates

    dom-awk            read HTML or XML into DOM object and process it with Ruby

    header-sort        sort file, keeping header in place

    highlight          highlight text matching REGEX

    json-awk           read JSON objects from standard input and process them with Ruby

    set-diff           find lines in first file which are not in the second

    set-intersect      find lines common to two files
    
    strip-columns      trim whitespace from fields of TSV file
    
    tawk               awk, but uses tabs for FS and OFS by default

    tsv-to-csv         convert TSV to CSV

    tsv-to-json        convert TSV to JSON

    utf8-viewer        display Unicode points and optionally names of UTF-8 encoded file
    
    xlsx-to-csv        convert XLSX to CSV

# SETUP

To generate the man pages, `pandoc` must be installed.  On Mac go to

    http://johnmacfarlane.net/pandoc/installing.html

and download the installer.  On Ubuntu there is a package:

    $ sudo apt-get install pandoc

Then run these:

    $ sudo make setup.ruby

    $ sudo make setup.perl

Then run this, assuming the install directory is writable:

    $ make install

# HOW TO RUN

    csv-to-json        [-d DELIMITER] [-q QUOTECHAR] < CSV_INPUT
    
    csv-to-tsv         [-e|-x|-r[z]] < CSV_INPUT

    date-seq           [--format=FMT] [--weekdays=DAY[,DAY]...] YYYY[MM[DD[HH]]] YYYY[MM[DD[HH]]]

    dom-awk            [-x|-h] [-f FILE] RUBY_SCRIPT

    header-sort        [OPTIONS] FILE

    highlight          REGEX < INPUT

    json-awk           [-j|-t] RUBY_SCRIPT < JSON_INPUT

    set-diff           FILE1 FILE2

    set-intersect      FILE1 FILE2

    tsv-to-csv         [-d DELIMITER] [-q QUOTECHAR] [-u] < TSV_INPUT

    utf8-viewer        [-b|-c|-n|-r] [-w NUM] [FILE]

    utf8-viewer        [-b|-c|-n|-r] -a BYTE ...

    xlsx-to-csv        XLSX_FILE DIRECTORY

    xlsx-to-csv        --sheet=SHEET XLSX_FILE OUTPUT_FILE
    
    xlsx-to-csv        --list

    tsv-to-json        < TSV_INPUT
