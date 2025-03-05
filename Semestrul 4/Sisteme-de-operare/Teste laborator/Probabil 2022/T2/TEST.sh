#!/bin/bash

if [[ $# != 1 ]] 
then 
    echo  "Usage: $0 <output_file>"
    exit 1
else
    echo -n "" > $1
    while read -r chars || [ -n "$chars" ]
    do 
        echo $chars
        echo $chars >> $1
    done
fi
cat $1