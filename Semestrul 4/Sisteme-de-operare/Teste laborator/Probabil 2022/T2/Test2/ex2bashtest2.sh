if test $# > 1 
then
val=0
i=0
n=$#

for n
do
	val=`expr $val + $1`
	i=`expr $i + 1`
	shift 1
done
val=`expr $val / $i`
echo "$val"

else
	echo "Nr de argumente prost"
fi