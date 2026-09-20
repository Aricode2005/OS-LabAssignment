#!/bin/bash
read -p "Enter the filename:" filename
read -p "Enter the string to search for:" word

if [ ! -f "$filename"];then
    echo "Error: File '$filename' does not exist."
    exit 1
fi

if [ "$total" -eq 0 ];then
   echo "The word '$word' was not found in the file."
else
    echo "Total occurrences of '$word' in the file: $total"
    echo "----------------------------------------"
    
total=$(grep -o "$word" "$filename" | wc -l)

grep -n "$word" "filename" | while read -r line_data; do
 
   line_num=$(echo "$line_data" | cut -d: -f1)
   line_text=$(echo "$line_data" | cut -d: -f2-)
   line_freq=$(echo "$line_text" | grep -o "$word" | wc -l)

   echo "Line Number: $line_num | Frequency: $line_freq"

   done

fi