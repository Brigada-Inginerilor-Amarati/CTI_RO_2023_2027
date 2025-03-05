#!/bin/bash
if [[ "$2" = "+" ]]
then result=$(($1+$3))
elif [[ "$2" = "-" ]]
then result=$(($1-$3))
elif [[ "$2" = "*" ]]
then result=$(($1*$3))
elif [[ "$2" = "/" ]]
then result=$(($1/$3))
fi

[[ -z $result ]] &&  echo "Nu exista un rezultat!" || echo "Metoda if-then-else: $result"

case "$2" in
"+" ) result1=$(($1+$3));;
"-" ) result1=$(($1-$3));;
"*" ) result1=$(($1*$3));;
"/" ) result1=$(($1/$3));;
esac

[ -z $result1 ] &&  echo "Nu exista un rezultat!" || echo "Metoda switch-case: $result1"