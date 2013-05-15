
# SUMMARY

File format conversion tools.

# SETUP

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
