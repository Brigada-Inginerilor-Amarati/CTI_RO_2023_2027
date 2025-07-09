#!/bin/bash
# ./prog.sh DIR
# numaram din fiecare fisier cate linii indeplinesc :
    # incepe cu A-Z
    # contine a-z A-Z 0-9, _, ,
    #se incheie cu punct

#afisam pe ecran count

# mai afisam un count pt verificare adrese ip

# m = cat | grep | wc -l 

DIR=$1

count=0
ipCount=0


# for file in $(find $DIR -type f); do
#     lines=$(cat $file | grep "^[A-Z].*[a-zA-Z0-9_,]*\.$" | wc -l)
#     count=$(($count + $lines))
# done

for arg in "$DIR"/*
do
    if [ -d "$arg" ] 
    then
        rec=`bash "$0" "$arg"`
        count=`expr $count + $rec`
    fi

    if [ -f "$arg" ]
    then
        #lines=`cat $arg | grep -E "^[A-Z][a-zA-Z0-9_, ]*\.$" | wc -l`
<<<<<<< HEAD
        lines=`cat $arg | grep -E "..." | wc -l`
=======
        lines=`cat $arg | grep -E "" | wc -l`
        #  lines=$(grep -E "^((25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])\.){3}(25[0-5]|2[0-4][0-9]|1[0-9]{2}|[1-9]?[0-9])$" "$arg" | wc -l)
>>>>>>> refs/remotes/origin/main
        if test $lines -ne 0 
        then
            count=`expr $count + $lines`
        fi
    fi
done

echo "$count"
