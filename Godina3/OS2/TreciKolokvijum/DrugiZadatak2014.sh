#!/bin/bash

if [ $OPTIND -lt 3 ];then
    exit 1
fi

file=$1
user=$2
shift
shift

if [ ! ( -f $file ) ] ; then
    exit 1
fi

groupsCounter=0
while [ $# -gt 0 ]; do
    groups[$groupsCounter]=$1
    groupsCounter=$(( $groupsCounter + 1 ))
    shift
done

oldIFS=IFS
IFS='\n'

index=-1
linesCounter=0
for i in $(cat $file) ; do
    name= $(echo $i | sed "s:\([a-zA-Z]\+\) .*:\1:")
    if [ $user == $name ]; then
        index=$linesCounter
    fi
    lines[$linesCounter]=$i
    linesCounter=$(( $linesCounter + 1 ))
done

if [ $index -eq -1 ] ; then
    for (( i=0; i<groupsCounter; i++ )) ; do
        line="$line $(echo ${groups[$i]})"
    done
    lines[$linesCounter]=$line
    linesCounter=$(( $linesCounter + 1 ))
else
    line=$(echo ${lines[$index]})
    line=$(echo $line | sed "s:[a-zA-Z]\+ \(.*\):\1:")
    for (( i=0; i<groupsCounter; i++ )) ; do
        if echo $line | grep $(echo ${groups[$i]}); then
            continue
        else
            line="$line $(echo ${groups[$i]})"
        fi
        
    done
fi

rm $file
touch $file
for (( i=0; i<linesCounter; i++ )) ; do
    echo ${lines[$i]} > $file
done
