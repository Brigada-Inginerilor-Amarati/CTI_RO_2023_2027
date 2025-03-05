#!/bin/bash

if [[ $# < 1 ]]
then
    echo "Usage: $0 <nr1> <nr2> <nr3> ..."
    exit 1
else
    c=0;
    sum=0
    for num
    do
        sum=$(($sum+$num))
        c=$(($c+1))
    done
    echo $(($sum/$c))
fi
