
#creati 3 variabile
var1=ana
var2="ana are mere"
var3=13

#afisati cele 3 variabile
echo $var1
echo $var2
echo $var3

if (($var1 = $var2))
then
    echo "sunt egale din punct de vedere lexicografic"
else
    echo "nu sunt egale"
fi

if test $var1 = $var2
then
    echo "sunt egale din punct de vedere lexicografic"
else
    echo "nu sunt egale"
fi


