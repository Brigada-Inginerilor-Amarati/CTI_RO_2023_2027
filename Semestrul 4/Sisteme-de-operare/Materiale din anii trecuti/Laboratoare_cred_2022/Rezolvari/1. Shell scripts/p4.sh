#!/bin/bash

if [ -d "$1" ] && [ "$2" = "x" -o "$2" = "w" -o "$2" = "r" ]
then 
    for file in `find $1 -print | grep ".txt"`
    do
        chmod +$2 $file
    done
else echo "Bad configuration!"
fi