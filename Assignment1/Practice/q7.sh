#!/bin/bash

read -r -p "Enter the filename: " filename
read -r -p "Enter the word to search for: " word

if [ ! -f "$filename" ];then
   echo "Error: File '$filename' does not exist."
   exit 1
fi
read -r -p "Enter the second word (to replace the first): " word2

total_count=$(grep -o "$word" "$filename" | wc -l)
exact_count=$(grep -o "\b$word\b" "$filename" | wc -l)
nocase_count=$(grep -i -o "\b$word\b" "$filename" | wc -l)

if [ $nocase_count -gt 0 ] && [ $nocase_count -ne $exact_count ]; then

    echo "No case count exists.."
fi

if [ $total_count -gt $exact_count ];then 
  echo "Partial matches exists..."

fi

if [ $exact_count -gt 0 ]; then
   echo "Exact matches exits.."
   sed -i "s/\b$word\b/$word2/g" "$filename"
   echo "Success: Exact matches have been replaced with '$word2'."
else
   echo "No exact matches exits.."
fi
