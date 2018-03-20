#!/bin/bash

if [ $OPTIND -lt 4 ];then
    exit 1
fi

file=$1
train=$2
hour=$3
min=$4

if [ ! ( -f $file ) ]; then
    exit 1
fi

oldIFS=$IFS
IFS='\n'

for i in $(cat "$file"); do
    serialNumber=$(echo $i | sed "s:\([0-9]\+\).*:\1:")
    if [ $serialNumber -eq $train ]; then
        restOfLine=$(echo $i | sed "s:[0-9]\+ \(.*\):\1:")
        IFS=' '
        minM=60
        minH=24
        for j in $restOfLine; do
            h=$(echo $j | sed "s:\([0-9][0-9]\).*:\1:")
            m=$(echo $j | sed "s;.*:\([0-9][0-9]\);\1;")
            if [ ( $h -gt $hour -o $h -eq $hour -a $m -gt $min ) -a ( $h -lt $minH -o $h -eq $minH -a $m -lt $minM ) ]; then
                minH=$h
                minM=$m
            fi
        done

        echo $minH:$minM 
        break
    fi
done

IFS=$oldIFS
