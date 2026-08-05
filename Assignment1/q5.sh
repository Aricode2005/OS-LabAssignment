#!/bin/bash

if [ "$#" -ne 4 ]; then
    echo "Error: You must provide exactly 4 file names."
    echo "Usage: $0 file1.java file2.java file3.java file4.java"
    exit 1
fi

printf "%-20s | %-10s | %-10s | %-10s\n" "File Name" "public" "class" "int"
printf "%s\n" "------------------------------------------------------------------"

for file in "$@"; do
    if [ -f "$file" ]; then
        count_public=$(grep -o "\bpublic\b" "$file" | wc -l)
        count_class=$(grep -o "\bclass\b" "$file" | wc -l)
        count_int=$(grep -o "\bint\b" "$file" | wc -l)
        
        printf "%-20s | %-10d | %-10d | %-10d\n" "$file" "$count_public" "$count_class" "$count_int"
    else
        printf "%-20s | %-35s\n" "$file" "Error: File not found"
    fi
done