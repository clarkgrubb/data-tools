% XLSX-TO-CSV(1)
% Clark Grubb
% May 4, 2013
`
# NAME

xlsx-to-csv - convert .xlsx to .csv

# SYNOPSIS

xlsx-to-csv XLSX_FILE DIRECTORY

# DESCRIPTION

Read a .xlsx file and create a .csv file in DIRECTORY for each worksheet.

DIRECTORY must not already exist.

.xlsx files are the format used by Excel since 2007.  The .xlsx file format is an Open Office XML file formats defined by ECMA-376.  An .xlsx file is a ZIP archive of a directory containing XML documents.

Before 2007 Excel used the .xls format.  `xlsx-to-csv` cannot read .xls files.

# OPTIONS

None

# SEE ALSO

`csv-to-tsv` (1)

http://www.ecma-international.org/publications/standards/Ecma-376.htm
             
