#!/bin/bash
if [ "$#" -ne 4 ]; then
    echo "Error: You must provide exactly 4 file names."
    echo "Usage: $0 file1.java file2.java file3.java file4.java"
    exit 1
fi



for file in "$@"; do
  if [ -f "$file" ]; then
     count_public=$(grep -o "\bpublic\b" "$file" | wc -l)
     count_class=$(grep -o "\bclass\b" "$file" | wc -l)
     count_private=$(grep -o "\bprivate\b" "$file" | wc -l)

    echo -e "$file\ncount_public:$count_public\ncount_class:$count_class\ncount_private:$count_private"
  else
     echo "Warning: '$file' is not a valid file. Skipping."
  fi
done 
  
