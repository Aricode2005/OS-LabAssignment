#!/bin/bash

TRASH_DIR="my-deleted-files"

if [ ! -d "$TRASH_DIR" ]; then
    mkdir "$TRASH_DIR"
fi

if [ "$1" == "-cl" ]; then
    read -r -p "Are you sure you want to clear the entire '$TRASH_DIR' directory? (y/n): " confirm
    if [ "$confirm" == "y" ]; then
        rm -rf "$TRASH_DIR"/*
        echo "Trash cleared."
    else
        echo "Operation cancelled."
    fi
    exit 0
fi

for file in "$@"; do
    if [ ! -f "$file" ]; then
        echo "Error: File '$file' does not exist."
        continue
    fi

    base_name=$(basename "$file")
    target="$TRASH_DIR/$base_name"

    if [ -e "$target" ]; then
        if [ ! -e "${target}_0" ]; then
            mv "$target" "${target}_0"
        fi

        version=1
        while [ -e "${target}_${version}" ]; do
            version=$((version + 1))
        done

        mv "$file" "${target}_${version}"
        echo "Moved '$file' to '$TRASH_DIR' as '${base_name}_${version}'."
    else
        mv "$file" "$target"
        echo "Moved '$file' to '$TRASH_DIR'."
    fi
done