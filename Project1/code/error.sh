#!/bin/bash
# comment out LU decomp code in poisson.cpp and write output of this
#      script to a file to get error points
COUNTER=1000
while [ $COUNTER -lt 251000 ]
do
    ./poisson_solve $COUNTER
    let COUNTER=$COUNTER+1000
done
