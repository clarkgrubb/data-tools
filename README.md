
# SUMMARY

File format conversion tools.

    csv-to-tsv         convert CSV to TSV

    dom-awk            read HTML or XML into DOM object and process it with Ruby

    json-awk           read JSON objects from standard input and proces them with Ruby

    set-diff           find lines in first file which are not in the second

    set-intersect      find lines common to two files

    utf8-viewer        display Unicode points and optionally names of UTF-8 encoded file
    
    tsv-to-csv         convert TSV to CSV

    weekdays           list weekdays in range

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

    csv-to-tsv         [-e|-x|-r[z]] < CSV_INPUT

    dom-awk            [-x|-h] [-f FILE] RUBY_SCRIPT

    json-awk           [-j|-t] RUBY_SCRIPT < JSON_INPUT

    set-diff           FILE1 FILE2

    set-intersect      FILE1 FILE2

    utf8-viewer        [-b|-c|-n|-r] [-w NUM] [FILE]

    utf8-viewer        [-b|-c|-n|-r] -a BYTE ...

    tsv-to-csv         [-d DELIMITER] [-q QUOTECHAR] [-u] < TSV_INPUT

    weekdays           WEEKDAY FMT STARTDATE ENDDATE

    xlsx-to-csv        XLSX_FILE DIRECTORY
