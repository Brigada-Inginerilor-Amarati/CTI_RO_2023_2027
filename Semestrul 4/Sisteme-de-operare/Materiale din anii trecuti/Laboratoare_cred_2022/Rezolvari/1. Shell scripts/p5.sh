#!/bin/bash

if [ -d "$1" ]
then
    total=0
    true > $2
    for file in `find $1 -print | grep ".txt"`
    do
        size=`wc -m $file | awk '{print $1}'`
        file=`wc -m $file | awk '{print $2}'`
        echo "$file: $size" >> $2
        total=$(($size+$total))
    done
    echo "TOTAL: $total" >> $2
else echo "Bad configuration!"
fi
