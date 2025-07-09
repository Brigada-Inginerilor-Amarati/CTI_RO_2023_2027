#!/bin/bash

var1="Ana"
var2="Aajaa11"
var3="12345"
var4="11Abc"

#facem expresii regex
# verificam daca var1 incepe cu cifre

if [[ $var1 =~ ^[0-9] ]]; then
    echo "var1 incepe cu cifre"
else
    echo "var1 nu incepe cu cifre"
fi

#sau

if echo "$var1" | grep -E "^[0-9]"; then
    echo "var1 incepe cu cifre"
else
    echo "var1 nu incepe cu cifre"
fi

# verificam daca se inceapa cu cifre si litere

if [[ $var2 =~ ^[0-9a-zA-Z] ]]; then
    echo "var2 incepe cu cifre si litere"
else
    echo "var2 nu incepe cu cifre si litere"
fi

# vrem sa aem o propozitie care se termina cu punct

if [[ $var3 =~ \.$ ]]; then
    echo "var3 se termina cu punct"
else
    echo "var3 nu se termina cu punct"
fi

# citim propozitii din linie de comanda (un email ) si sa l verificam daca este corect( contine @ si .)
# citire de linii de la tastatura cu un while si cu un read
# inainte de @ nu trebuie sa fie ., dar poate fi _

regex="^[a-zA-Z0-9_]+@[a-zA-Z0-9]+\.[a-zA-Z]{2,4}$"

while read -p "Introduceti un email: " email; do
    if [[ $email =~ $regex ]]; then
        echo "Email corect"
        break
    else
        echo "Email incorect"
    fi
done

# si daca vreau sa citesc mai multe emailuri

while true; do
    read -p "Introduceti un email: " email
    if [[ $email =~ $regex ]]; then
        echo "Email corect"
    else
        echo "Email incorect"
    fi
    read -p "Doriti sa introduceti un alt email? (y/n)" raspuns
    if [ $raspuns == "n" ]; then
        break
    fi
done