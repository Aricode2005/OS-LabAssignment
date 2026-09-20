#!/bin/bash

read -r -p "Enter the file name to search: " filename
read -r -p "Enter the first word (to search for): " word1

if [ ! -f "$filename" ]; then
    echo "Error: File '$filename' does not exist."
    exit 1
fi

read -r -p "Enter the second word (to replace the first): " word2

echo -e "\n--- Search & Replace Results ---"

exact_count=$(grep -o "\b$word1\b" "$filename" | wc -l)
total_count=$(grep -o "$word1" "$filename" | wc -l)
nocase_count=$(grep -i -o "\b$word1\b" "$filename" | wc -l)

if [ "$nocase_count" -gt 0 ] && [ "$nocase_count" -ne "$exact_count" ]; then
    echo "Notice: A match exists if case sensitivity is ignored."
fi

if [ "$total_count" -gt "$exact_count" ]; then
    echo "Notice: Partial matches do exist."
fi

if [ "$exact_count" -gt 0 ]; then
    echo "Found $exact_count exact match(es) for '$word1'."
    
    sed -i "s/\b$word1\b/$word2/g" "$filename"
    
    echo "Success: Exact matches have been replaced with '$word2'."
else
    echo "No exact matches found. No replacements were made."
fi