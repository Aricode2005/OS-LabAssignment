#!/bin/bash
target_dir=${1:-.}

echo "Total number of files in $target_dir and subdirectories:"
find "$target_dir" -type f | wc -l

echo -e "\n(i) Number of files in each subdirectory:"
find "$target_dir" -type d | while read -r dir; do
    count=$(find "$dir" -maxdepth 1 -type f | wc -l)
    echo "Directory: $dir -> Files: $count"
done
echo -e "\n(ii) Files created/modified within the past week:"
find "$target_dir" -type f -mtime -7 -printf "%f\n"