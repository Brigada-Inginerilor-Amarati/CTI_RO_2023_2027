#!/bin/bash

# /.prog.sh fis.txt DIR
# parcurgem recursiv pe DIR si scriem in fis.txt toate path-urile fisierelor parcurse
# pentru fisiere obisnuite -> ln -s
# pentru fisier obisnuit -> count++
# count ul va fi scris in fis.txt

# pe linux fara ;
if [ $# -ne 2 ]; then
    echo "Numar invalid de argumente"
    exit 1
fi

fisier=$1
dir=$2
count=0


for arg in "$dir"/*;
do
    if [ -d "$arg" ]; then
        rec=$(bash $0 "$fisier" "$arg")
        count=`expr $count + $rec`
        echo "$arg" >> "$fisier"
    fi

    if [ -f "$arg" ]; then
        ln -s "$arg" "$fisier"
        count=$((count + 1))
    fi    
   
done

echo $count 
echo $count >> "$fisier"

