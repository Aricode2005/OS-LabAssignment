#!/bin/bash

read -p "Enter the number for factorial: " num

fact=1

start_time=$(date +%s%N)

for(( i=1 ; i<=num ; i++ ));do
   fact=$((fact*i));
done
end_time=$(date +%s%N)

time_taken=$((end_time-start_time))

echo "The factorial of $num is $fact"
echo "Time taken to calculate: $time_taken nanoseconds"