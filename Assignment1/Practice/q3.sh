#!/bin/bash

dir="$1"

echo "a)Total Count of files and directories:"
find "$dir" -mindepth 1 -maxdepth 1 | wc -l

echo -e "\nb) Total Files:"
find "$dir" -maxdepth 1 -type f | wc -l
find "$dir" -maxdepth 1 -type f 

echo -e "\nb) Total directories:"
find "$dir" -mindepth 1  -maxdepth 1 -type d | wc -l
find "$dir" -mindepth 1  -maxdepth 1 -type d | while read -r subdir;do
   filecount=$(find "$subdir" -maxdepth 1 -type f | wc -l)
   echo "$subdir:$filecount files"
done

find "$dir" -type f -mtime -7 -printf '%s\n' | awk '{sum += $1} END {print sum}'



