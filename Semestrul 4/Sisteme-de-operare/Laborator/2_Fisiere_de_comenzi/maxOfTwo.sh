#!/bin/bash

nr1=$1
nr2=$2

if [ "$nr1" -gt "$nr2" ]
then
    echo "$nr1"
else   
    echo "$nr2"
fi