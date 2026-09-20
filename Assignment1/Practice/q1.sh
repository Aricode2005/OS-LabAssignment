#!/bin/bash
if [ "$#" -ne 8 ];then
    echo "Please provide exactly 8 arguments.."
    exit 1
fi

echo "There are $# arguments"
echo "$8 $1 $2 $3 $4 $5 $6 $7"