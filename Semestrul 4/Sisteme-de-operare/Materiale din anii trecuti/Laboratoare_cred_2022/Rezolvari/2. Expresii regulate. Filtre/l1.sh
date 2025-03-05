#!/bin/bash
areParenthesesClosed() {
    onlyParentheses=$(echo $1 | grep -o "[()]" | tr -d '\n')
    while [[ $(echo $onlyParentheses | grep "[(][)]") ]]
    do
        onlyParentheses=$(echo $onlyParentheses | sed 's/()//' )
    done

    [[ ! $(echo $onlyParentheses | grep "[()]") ]]
}

isExpression()
{
    range="[^0-9a-zA-Z\-+\(\)]"
    wrongStart="^[+\-\)]"
    wrongEnd="[+\-\(]$"
    wrongOpPosition="[+\-\(][\-+\)]"
    if [[ $1 =~ $range || $1 =~ $wrongEnd || $1 =~ $wrongStart || $1 =~ $wrongOpPosition ]] || (! areParenthesesClosed $1)
    then 
        false
    else
        true
    fi
}

while read -r line
do
    if isExpression $line
    then
        echo $line
    else
        echo eroare
    fi
done

