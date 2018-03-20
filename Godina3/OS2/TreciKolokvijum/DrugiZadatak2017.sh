#!/bin/bash

if [ $OPTIND -lt 3 ];then
    exit 1
fi

template=$1
folder=$2
access=$3

for i in $(ls "$folder" -R); do
    if [ -f $i ]; then
        if echo $i | grep "$template" > /dev/null; then
            chmod a+$access $i
        fi
    fi
done
