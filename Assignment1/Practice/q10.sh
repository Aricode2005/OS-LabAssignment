#!/bin/bash

THRASH_DIR="my_deleted_files"

if [ ! -d "$TRASH_DIR" ]; then
    mkdir "$TRASH_DIR"
fi

if [ "$1" == "-cl"];then
   read -r -p "Are you sure want to delete the '$THRASH_DIR' (y/n)? " confirm
   if [ "$confirm" == "y" ];then
     rm -rf "$THRASH_DIR"/*
     echo "Thrash Cleared."
   else
     echo "Operation failed."
   fi
fi

for file in "$@" ;do
  if [ ! -f "$file"];then
    echo "File does not exits.."
  fi

  base_name=$(basename "$file")
  target="$THRASH_DIR/$base_name"
  if [ -e "$target" ];then
     if [ ! -e "${target}_0" ];then 
        mv "$target" "${target}_0"
     fi

     version=1
     while [ -e "${target}_${version}" ];do
           version=$((version+1))
     done
     mv "$file" "${target}_${version}"
     echo "Moved '$file' to '$TRASH_DIR' as '${base_name}_${version}'."
  else
     mv "$file" "$target"
    echo "Moved '$file' to '$TRASH_DIR'."
  fi


done
  
