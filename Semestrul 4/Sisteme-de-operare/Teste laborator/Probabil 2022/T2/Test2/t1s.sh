#!/bin/bash

if [[ $# < 1 ]] 
then 
    echo  "Usage: $0 <entry1> <entry2> ..."
    exit 1
else
    sum=0
    for path
    do
        if [[ -f $path ]]
        then
            current=$(./t1 "$path")
            sum=$(($sum + $current))
        fi
    done
    echo "Sum: $sum"
fi