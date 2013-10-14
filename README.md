
# SUMMARY

Mostly data extraction and file format conversion tools.  Take [the tour](https://github.com/clarkgrubb/data-tools/blob/master/doc/TOUR.md) for a more verbose introduction to the tools.

    csv-to-json        convert CSV to JSON

    csv-to-tsv         convert CSV to TSV

    date-seq           create a sequence of dates

    dom-awk            read HTML or XML into DOM object and process it with Ruby

    header-sort        sort file, keeping header in place

    hexedit            edit a binary file

    highlight          highlight text matching REGEX

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

# SETUP

To install the necessary Ruby gems and Python packages:

    $ sudo make setup

Then run this to put the *data tools* in your path.  It must be run with permission to create files in the install directory; it creates symlinks to the source directory:

    $ make install

If you don't like the choice of install directory (`/usr/local/bin`), you can override it by setting the `LOCAL_INSTALL_DIR` environment variable.

To generate and install man pages `pandoc` must be installed.  On Mac go to

    http://johnmacfarlane.net/pandoc/installing.html

and download the installer.  On Ubuntu there is a package:

    $ sudo apt-get install pandoc

Then run this:

    $ make install-man

# HOW TO RUN

    csv-to-json        [-d DELIMITER] [-q QUOTECHAR] [CSV_FILE]
    
    csv-to-tsv         [-e|-x|-r[z]] [CSV_FILE]

    date-seq           [--format=FMT] [--weekdays=DAY[,DAY]...] YYYY[MM[DD[HH]]] YYYY[MM[DD[HH]]]

    dom-awk            [-x|-h] [-f SCRIPT] RUBY_SCRIPT [HTML_OR_XML_FILE]

    header-sort        [OPTIONS] FILE

    hexedit            [-m|-s] FILE

    highlight          REGEX [FILE]
    
    highlight          (--red|--green|--yellow|--blue|--magenta|--cyan)=REGEX ... [FILE]

    json-awk           [-j|-t] (--file=SCRIPT_PATH | RUBY_SCRIPT) [JSON_INPUT] ...

    reservoir-sample   [-r SEED] -s NUM [FILE]

    set-diff           FILE1 FILE2

    set-intersect      FILE1 FILE2

    trim-tsv           < INPUT

    tsv-to-csv         [-d DELIMITER] [-q QUOTECHAR] [-u] [TSV_FILE]

    tsv-to-json        [TSV_FILE]
    
    utf8-viewer        [-b|-c|-n] [-w NUM] [FILE]

    utf8-viewer        [-b|-c|-n] -a BYTE ...

    xls-to-csv         <same as xlsx-to-csv>

    xlsx-to-csv        [--date-format=DATE_FMT] XLSX_FILE DIRECTORY

    xlsx-to-csv        [--date-format=DATE_FMT] --sheet=SHEET XLSX_FILE [OUTPUT_FILE]
    
    xlsx-to-csv        --list XLSX_FILE
