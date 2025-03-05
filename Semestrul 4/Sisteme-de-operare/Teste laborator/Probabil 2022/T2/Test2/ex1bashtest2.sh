
val=0
if test $# > 1 
then
	gcc -Wall -o exec ex1test2.c
	nr=$#
	
	for nr
	do
	var=$1
	
	elec=$( ./exec $var | cut -f 1 )

	val=`expr $val + $elec`

	

	shift 1
	done

	echo $val

else
	echo "Nr insuficient de arg"
fi