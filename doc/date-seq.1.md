% DATE-SEQ(1)
% Clark Grubb
% June 17, 2013


# NAME

date-seq - print sequence of dates or times

# SYNOPSIS

date-seq [--format=FMT] [--weekdays=DAY[,DAY]...] YYYY[MM[DD[HH]]] YYYY[MM[DD[HH]]]

# DESCRIPTION

Generate a sequence of dates or times.

The command takes two arguments: the start date and the end date.  The generated sequence is inclusive.

The format of the date arguments is YYYY[MM[DD[HH[MI[SS]]]]]. As little as the year or as much as the second can be specified.  The end date must be the same length as the start date.

If the arguments have a YYYYMMDD format, the sequence will consist of days.  If the arguments have a YYYYMMDDHH format, the sequence will consist of hours.  Sequences of years, months, minutes, or seconds are also possible.

# OPTIONS

--format
: `strftime` style format string to control output.

--regex
: a regular expression which can be used to filter the sequence.  The regular expression should be written to apply to the YYYY[MM[DD[HH[MI[SS]]]]] format, not the output format specified by the --format flag.

--weekdays
: comma separated list of weekdays.  Dates for days outside the list are excluded.

# EXAMPLES

Every Monday, Wednesday, and Friday in October 2012:

    date-seq --weekdays=Mon,Wed,Fri 20121001 20121031

Every fourth day starting October 1, 2012:

    date-seq 20121001 20121101 | awk 'NR % 4 == 0'

The second day of each month of 2012 in YYYY-MM-DD format:

    date-seq --format='%F' --regex='.{6}02' 20120101 20121231

The 30 most recent days in YYYYMMDD format:

    date-seq 20100101 $(date +'%Y%m%d') | tail -30

# SEE ALSO

`strftime` (3), `seq` (1), `grep` (1), `awk` (1)
