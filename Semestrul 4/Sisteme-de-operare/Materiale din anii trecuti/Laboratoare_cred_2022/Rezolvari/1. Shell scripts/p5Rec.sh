#!/bin/bash

currentFolder=`pwd`
oldIFS=$IFS
IFS=$'\n'
total=0

function traverseDirectory()
{
  cd $1
  for file in `ls`
  do
    if [[ -d "$file" ]]
    then traverseDirectory $file $2
    elif [[ ${file: -4} = ".txt" ]]
    then
      size=`wc -m $file | awk '{print $1}'`
      file=`wc -m $file | awk '{print $2}'`
      echo "$file: $size" >> $2
      total=$(($size+$total))
    fi
  done
  cd ..
}

if [[ -d "$1" ]]
then
  true > $2
  traverseDirectory $1 $2
  echo "TOTAL: $total" >> $2
else
  echo "Bad configuration!"
fi

IFS=$oldIFS
