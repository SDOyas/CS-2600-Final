#!/bin/bash

array_name=(1 11 2 22 3 33 4 44);
a=0;
while true
  do
    r=$[ $RANDOM % 8 ]
    while [ $r -eq $a ]
    do 
        r=$[ $RANDOM % 8 ]
    done
    
    echo ${array_name[$r]};
    a=$r;
    sleep 1;
  done