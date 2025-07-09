#!/bin/sh

functieMax(){
    #<var>
    var1=$1
    var2=$2

    if [ $var1 -gt $var2 ]
        then 
        echo $var1
    else
        echo $var2
    fi
    #</var>
}

functieMax 13 2

# de ex daca rulam cu mai multe argumente in linie de comanda tot pe alea de la functieMax le ia