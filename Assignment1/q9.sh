#!/bin/bash

read -p "Enter an integer to find its factorial: " num

start_time=$(date +%s%N)

fact=1

for (( i=1; i<=num; i++ ))
do
    fact=$((fact * i))
done

end_time=$(date +%s%N)

time_taken=$((end_time - start_time))

echo "The factorial of $num is $fact"
echo "Time taken to calculate: $time_taken nanoseconds"