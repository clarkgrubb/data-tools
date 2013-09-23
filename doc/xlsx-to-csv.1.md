% XLSX-TO-CSV(1)
% Clark Grubb
% May 4, 2013

# NAME

xlsx-to-csv - convert .xlsx to .csv

# SYNOPSIS

    xlsx-to-csv XLSX\_FILE OUTPUT_DIR
    xlsx-to-csv --sheet=SHEET XLSX\_FILE [OUTPUT\_FILE]
    xlsx-to-csv --list XLSX\_FILE

# DESCRIPTION

Read a .xlsx file and create a .csv file in DIRECTORY for each worksheet.

DIRECTORY must not already exist.

Output is UTF-8 encoded.

.xlsx files are the format used by Excel since 2007.  The .xlsx file format defined by ECMA-376.  An .xlsx file is a ZIP archive of a directory containing XML documents.  The `unzip -l` command can be used to list the contents of a ZIP archive and hence an .xlsx file.

`xlsx-to-csv` also works on .xls files which were used by Excel before 2007.

The tool can easily take a minute or more to process a large (~100MB) workbook.  Unfortunately, it takes about this long just to list the sheet names with the `--list` flag.
Hence it is more efficient to extract all of the sheets from a large workbook even if only one of the sheets is needed.

# OPTIONS

--list
    : list the sheets in XLSX\_FILE
    
--sheet
    : only convert SHEET to a .csv file.

--date-format=STRFTIME_FMT
    : a `strftime` style format to be used for Excel dates.  The default is the ISO 8601 format: '%Y-%m-%dT%H:%M:%S'.

# SEE ALSO

`csv-to-tsv` (1), `strftime` (3)

http://www.ecma-international.org/publications/standards/Ecma-376.htm
             
