#!/bin/bash
dir="$1"

if [ ! -d "$dir" ]; then
  echo "Error: '$dir' is not a valid directory."
  exit 1
fi

echo "a) Total count of files and directories:"
find "$dir" -mindepth 1 -maxdepth 1 | wc -l

echo -e "\nb) Files and Directories Separately with Respective Counts:"


file_count=$(find "$dir" -mindepth 1 -maxdepth 1 -type f | wc -l)
echo "Total Files: $file_count"
echo "File Names:"
find "$dir" -mindepth 1 -maxdepth 1 -type f 

echo "------------------------"


dir_count=$(find "$dir" -mindepth 1 -maxdepth 1 -type d | wc -l)
echo "Total Directories: $dir_count"
echo "Directory Names:"
find "$dir" -mindepth 1 -maxdepth 1 -type d



echo -e "\nd) Total size of files created in the past week (in bytes):"
find "$dir" -type f -mtime -7 -printf "%s\n" | awk '{sum += $1} END {print sum+0}'