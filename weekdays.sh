#!/bin/bash

trap exit ERR

# make sure date -d is supported
#
date -d 20120101 +%a > /dev/null

#  TODO: re-write this in Ruby or Python
#  TODO: use named parameters
#  TODO: throw error if 3rd or 4th arg not integer

readonly WEEKDAYS='Mon Tue Wed Thu Fri Sat Sun'
readonly FIRSTYEAR=2000
readonly CURRENTYEAR=$(date +'%Y')

if [ $# -ne 4 ]
then
    echo "USAGE: weekdays WEEKDAY FMT STARTDATE ENDDATE"
    echo
    echo "WEEKDAY must be in: $WEEKDAYS"
    echo "FMT is a strftime style format: q.v. 'man strftime'"
    echo "STARTDATE and ENDDATE must be YYYYMMDD"
    exit 1
fi

readonly weekday=$1
readonly fmt=$2
readonly startdate=$3
readonly enddate=$4

for dow in $WEEKDAYS
do
    if [ $weekday = $dow ]
    then
        weekday_is_valid=1
    fi
done
if [ $week_is_valid ]
then
    echo "WEEKDAY must be one of: $WEEKDAYS"
    exit 1
fi

if [ $startdate -lt ${FIRSTYEAR}0101 ]
then
    echo "years cannot be before $FIRSTYEAR"
    exit 1
fi

if [ $enddate -gt ${CURRENTYEAR}1231 ]
then
    echo "years cannot be after $CURRENTYEAR"
    exit 1
fi

for yy in $(seq $FIRSTYEAR $CURRENTYEAR); do
  if [ \( $enddate -ge ${yy}0101 \) -a \( $startdate -le ${yy}1231 \) ]; then
    for mm in $(seq -w 01 12); do
      if [ \( $enddate -ge $yy${mm}01 \) -a \( $startdate -le $yy${mm}31 \) ]; then
        for dd in $(seq -w 01 31); do
          if [ \( $enddate -ge $yy$mm$dd \) -a \( $startdate -le $yy$mm$dd \) ]; then
            if date -d $yy$mm$dd > /dev/null 2>&1; then
              if [ $(date -d $yy$mm$dd +%a) = $weekday ]; then
                date -d $yy$mm$dd +$fmt
              fi
            fi
          fi
        done
      fi
    done
  fi
done
