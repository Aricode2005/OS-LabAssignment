#!/bin/bash

while true; do
    echo -e "\n----New Operation------"
    read -p "Enter first variable 'userv1' (or 'quit' to exit): " userv1
    
    if [ "$userv1" == "quit" ]; then break; fi
    
    read -p "Enter second variable 'userv2': " userv2

    regex='^[+-]?[0-9]+$'

    if [[ $userv1 =~ $regex ]] && [[ $userv2 =~ $regex ]]; then
        echo "The sum of '$userv1' and '$userv2' is $((userv1+userv2))"
        echo "The subtraction of '$userv1' and '$userv2' is $((userv1-userv2))"
        echo "The product of '$userv1' and '$userv2' is $((userv1*userv2))"

        if [ "$userv2" -eq 0 ]; then
            echo "Division Error: Cannot divide by zero."
        else
            echo "The division of '$userv1' and '$userv2' is $((userv1/userv2))"
        fi
    else
        echo "Error: Arithmetic operations cannot be performed because one or both variables are not integers."
    fi
    
    echo
    echo "Variables in reverse order: $userv2, $userv1"
done