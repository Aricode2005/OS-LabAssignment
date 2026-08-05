#!/bin/bash
dir=$1 

echo "a) Total count of files and directories:"
find "$dir" -mindepth 1 | wc -l

echo "b) Total Files:"
find "$dir" -maxdepth 1 -type f | wc -l
echo "List of Files:"
find "$dir" -maxdepth 1 -type f

echo "b) Total Directories:"
find "$dir" -mindepth 1 -maxdepth 1 -type d | wc -l
echo "List of Directories:"
find "$dir" -mindepth 1 -maxdepth 1 -type d

echo "c) Total size of files created in the past week (in bytes):"
find "$dir" -type f -mtime -7 -printf "%s\n" | awk '{sum += $1} END {print sum}'