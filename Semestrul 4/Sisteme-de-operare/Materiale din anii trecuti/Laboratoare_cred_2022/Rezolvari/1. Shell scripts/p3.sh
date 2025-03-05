#!/bin/bash
hour=`date +"%H"`
user=`whoami`
if [ $hour -lt 12 -a $hour -gt 6 ]
then echo "Buna dimineata, $user!"
elif [ $hour -lt 18 -a $hour -gt 12 ]
then echo "Buna ziua, $user!"
elif [ $hour -lt 22 -a $hour -gt 18 ]
then echo "Buna seara, $user!"
else echo "Noapte buna, $user!"
fi