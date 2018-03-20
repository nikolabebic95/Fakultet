#!/bin/bash

if [ $OPTIND -lt 1 ] ;then
    exit 1
fi

file=$1
if [ ! ( -f $file ) ] ; then
    exit 1
fi

oldIFS=IFS
IFS='\n'

counter=0
for i in $(cat $file) ; do
    array[$counter]=$i
    counter=$(( $counter+1 ))
done

for ((i=0; i<counter; i++)) ; do
    for ((j=i+1; j<counter; j++)) ; do
        year1=$(echo ${array[$i]} | sed "s:[0-9]\{2\}[A-Z][0-9]\{2\}\([0-9]\).*:\1:")
        year2=$(echo ${array[$j]} | sed "s:[0-9]\{2\}[A-Z][0-9]\{2\}\([0-9]\).*:\1:")
        if [ $year1 -gt $year2 ]; then
            tmp=$(echo ${array[$i]})
            array[$i]=$(echo ${array[$j]})
            array[$j]=$tmp
        fi
    done
done

echo ${array[*]}