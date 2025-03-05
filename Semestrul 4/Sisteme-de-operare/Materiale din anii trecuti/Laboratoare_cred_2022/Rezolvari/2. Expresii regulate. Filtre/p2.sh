#!/bin/bash

urlRegex="^(http:\/\/|https:\/\/)[a-z][a-zA-Z0-9\-\.]*\.(com|ro|eu)$"
macRegex="^[0-9A-F]{2}(:[0-9A-F]{2}){5}$"

if [[ $1 = "-i" && $3 = "-o" ]]
then
    true > $4
    for line in $(cat $2)
    do
        url=$(echo $line | cut -f 1 -d ";")  
        mac=$(echo $line | cut -f 2 -d ";")
        if [[ $url =~ $urlRegex && $mac =~ $macRegex ]]
        then 
            echo "OK" >> $4
        else
            echo "ERROR" >> $4
        fi
    done

else
    echo "Usage: ./script.sh -i <input_file> -o <output_file>"
fi