% WEEKDAYS(1)
% Clark Grubb
% May 6, 2013


# NAME

weekdays - list weekdays in range

# SYNOPSIS

weekdays WEEKDAY FMT STARTDATE ENDDATE

# DESCRIPTION

List every Monday (or Tuesday, Wednesday, etc) between STARTDATE and ENDDATE.

WEEKDAY is the desired day of the week.  It must be on of

    Sun Mon Tue Wed Thu Fri Sat

The output format is controlled by FMT.  It uses the same format specifiers as
`strftime`.  Examples are '%Y-%m-%d' or '%Y%m%d'.

# OPTIONS

None

# BUGS

Does not work on Mac OS X because it requires a version of the `date` command
which supports the -d flag.

# SEE ALSO

`date` (1)

`strftime` (3)