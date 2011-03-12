#!/bin/bash

i=1

while [ $i -le  5 ]
do
    echo ' '
    echo "test ${i}"
    $1 < ${i}.in
    echo ' '
    cat ${i}.ans
    echo ' '
    i=$(( $i + 1 ))
done


