#!/bin/bash

# Verificare daca avem 3 argumente

if [ "$#" -ne 3 ]
then
    echo "Utilizare incorecta, corect era : $0 <nr1> <nr2> <nr3>"
    exit 1
fi

# atribuim valorile

nr1=$1
nr2=$2
nr3=$3

# determinam maximul

max=$nr1

if [ "$nr2" -gt "$max" ]
then
    max=$nr2
fi

if [ "$nr3" -gt "$max" ]
then
    max=$nr3
fi

# afisam rezultat
echo "$max"