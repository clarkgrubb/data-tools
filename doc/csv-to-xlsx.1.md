% CSV-TO-XLSX(1)
% Clark Grubb
% November 7, 2013


# NAME

csv-to-xlsx - convert CSV files to XLSX worksheets

# SYNOPSIS

csv-to-xlsx -o|--output-file XLSX\_PATH CSV\_PATH ...

# DESCRIPTION

Create an XLSX workbook from the CSV files specified on the command line.

Each CSV file becomes a worksheet in the workbook.

The names of the worksheets are derived from CSV file names.  Excel worksheet names are limited to 31 characters and these characters are forbidden:

    [ ] * ? / \ .
    
`csv-to-xlsx` replaces forbidden characters with spaces, squeezes multiple adjacents spaces to a single space, truncates to 31 characters, and trims marginal space.  If this results in multiple sheets with the same name an error is generated.

XLSX is the default format used by Excel 2007 and later.

# OPTIONS

-o DELIMITER, \--output-file PATH
: the PATH of the XLSX file to create.  It must have an .xlsx suffix.

# SEE ALSO

`xlsx-to-csv` (1)

http://www.ietf.org/rfc/rfc4180.txt

http://www.ecma-international.org/publications/standards/Ecma-376.htm

