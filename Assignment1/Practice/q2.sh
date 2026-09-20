#!/bin/bash
while true; do
  echo -e "\n------New operation-----"
  read -p "Enter the first variable or type 'quit' to exit:" userv1
  if [ "$userv1" == "quit" ]; then break ; fi
  read -p "Enter the second variable or type 'quit' to exit:" userv2
  if [ "$userv2" == "quit" ]; then break ; fi

  regex='^[+-]?[0-9]+$'

  if [[ $userv1 =~ $regex ]] && [[ $userv2 =~ $regex ]]; then 
     
     echo "The sum of the two variables : $((userv1+userv2))"
     echo "The difference of the two variables: $((userv1-userv2))"
     echo "The product of the two variables: $((userv1*userv2))"

     if [ "$userv2" -ne 0 ];then
        echo "The division of the two variables: $((userv1/userv2))"
     else
        echo "Division by zero not possible.."
     fi
  else
    echo "Error:Arithmetic operations cannot be done on string literals."
  fi 
  echo "Variables in reverse order: $userv2, $userv1"
done 
