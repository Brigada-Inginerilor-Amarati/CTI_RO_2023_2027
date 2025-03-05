#!/bin/bash

emailRegex="^[a-zA-Z][a-zA-Z0-9]*@[a-zA-Z][a-zA-Z0-9]*\.(com|ro|eu)$"
ipGroupNo0="(2(5[0-5]|[0-4][0-9])|1[0-9][0-9]|[1-9][0-9]|[1-9])"
ipGroup="(25[0-5]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"
ipGroupNo255="(25[0-4]|2[0-4][0-9]|1[0-9][0-9]|[1-9]?[0-9])"
ipRegex="^$ipGroupNo0(\.$ipGroup){2}\.$ipGroupNo255$"

if [[ $1 = "-i" && $3 = "-o" ]]
then
    true > $4
    for line in $(cat $2)
    do
        email=$(echo $line | cut -f 1 -d ";")  
        ip=`echo $line | cut -f 2 -d ";"` 
        if [[ $email =~ $emailRegex && $ip =~ $ipRegex ]]
        then 
            echo "OK" >> $4
        else
            echo "ERROR" >> $4
        fi
    done

else
    echo "Usage: ./script.sh -i <input_file> -o <output_file>"
fi