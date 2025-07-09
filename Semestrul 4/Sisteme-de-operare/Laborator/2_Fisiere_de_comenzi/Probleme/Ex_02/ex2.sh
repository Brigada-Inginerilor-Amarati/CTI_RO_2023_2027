#!/bin/bash

# Verificare daca avem 3 argumente

if [ "$#" -ne 3 ]; then
    echo "Utilizare incorecta, corect era : $0 <op1> <operator> <op2>"
    exit 1
fi

operand1=$1
operator=$2
operand2=$3

if [ "$operator" = "+" ]; then
    result=$((operand1+operand2))
elif [ "$operator" = "-" ]; then
    result=$((operand1-operand2))
elif [ "$operator" = "*" ]; then
    result=$((operand1*operand2))
elif [ "$operator" = "/" ]; then
    
