#!/bin/bash

currentFolder=`pwd`
oldIFS=$IFS
IFS=$'\n'
function analizeDirectory()
{
  cd $1
  for file in `ls`
  do
    if [[ -d "$file" ]]
    then analizeDirectory "$file" $2
    elif [[ ${file: -4} = ".txt" ]]
    then chmod +$2 $file
    fi
  done
  cd ..
}

if [[ -d "$1" ]] && [[ "$2" = "x" || "$2" = "w" || "$2" = "r" ]]
then
  analizeDirectory $1 $2
else
  echo "Bad configuration!"
fi
IFS=$oldIFS
