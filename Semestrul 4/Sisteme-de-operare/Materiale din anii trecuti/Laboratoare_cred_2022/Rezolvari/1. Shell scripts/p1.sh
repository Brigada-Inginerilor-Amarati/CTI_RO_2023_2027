#!/bin/bash
if [[ $# = 3 ]]
then
	max=$1;
	for num in $@
	do
		if [[ $max < $num ]]
		then max=$num
		fi
	done
	echo $max
else echo "Numarul de argumente este invalid!"
fi
