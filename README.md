
# SUMMARY

File format conversion tools.

# SETUP

To generate the man pages, `pandoc` must be installed.  On Mac go to

    http://johnmacfarlane.net/pandoc/installing.html

and download the installer.  On Ubuntu there is a package:

    $ sudo apt-get install pandoc

The run these:

    $ sudo make setup.ruby

    $ sudo make setup.perl

Then run this, assuming the install directory is writable:

    $ make install

# HOW TO RUN

    csv-to-tsv         [-e|-x|-r[z]] < CSV_INPUT

    dom-awk            [-x|-h] [-f FILE] RUBY_SCRIPT

    file-count-split   --count COUNT --file FILE --prefix PREFIX

    json-awk           [-j|-t] RUBY_SCRIPT < JSON_INPUT

    set-diff           FILE1 FILE2

    set-intersect      FILE1 FILE2

    utf8-to-unicode    [-n|--name] BYTE ...

    tsv-to-csv         [-d DELIMITER] [-q QUOTECHAR] [-u] < TSV_INPUT

    weekdays           WEEKDAY FMT STARTDATE ENDDATE

    xlsx-to-csv        XLSX_FILE DIRECTORY
