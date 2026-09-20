#!/bin/bash

if [ "$#" -ne 2 ];then
  exit 1
fi

date_fmt1=$(echo "$1" | awk -F/ '{print $3"-"$2"-"$1}')
date_fmt2=$(echo "$2" | awk -F/ '{print $3"-"$2"-"$1}')


day1=$(date -d "$date_fmt1" +%A)
day2=$(date -d "$date_fmt2" )
echo "$day2"

if [ "$day1" == "$day2" ];then
    echo "Result: Match! Both people were born on a $day1."
else
    echo "Result: No match."
fi

   