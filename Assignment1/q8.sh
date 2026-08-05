#!/bin/bash

if [ "$#" -ne 2 ]; then
    echo "Usage: ./birthday_match.sh DD/MM/YYYY DD/MM/YYYY"
    exit 1
fi

date1_fmt=$(echo "$1" | awk -F/ '{print $3"-"$2"-"$1}')
date2_fmt=$(echo "$2" | awk -F/ '{print $3"-"$2"-"$1}')

day1=$(date -d "$date1_fmt" +%A)
day2=$(date -d "$date2_fmt" +%A)

echo "Person 1 ($1) was born on a $day1."
echo "Person 2 ($2) was born on a $day2."
echo "----------------------------------------"

if [ "$day1" == "$day2" ]; then
    echo "Result: Match! Both people were born on a $day1."
else
    echo "Result: No match."
fi