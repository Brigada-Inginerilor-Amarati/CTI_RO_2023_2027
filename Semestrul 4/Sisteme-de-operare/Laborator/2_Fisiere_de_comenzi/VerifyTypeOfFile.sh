#!/bin/bash

#creati un script care verifica daca un fisier este fisier normal sau legatura simbolica

fisier1=$1

if test -f $fisier1
then   
    echo "legatura simbolica!"
elif test -L $fisier1
then   
    echo "fisier obisnuit!"
fi

