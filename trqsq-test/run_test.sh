#!/bin/bash

dims=(2 3 4 5 6 7 8 9 10)
iterations=(10000 100000 500000 1000000)

for dim in "${dims[@]}"; do
    for iters in "${iterations[@]}"; do
	#echo $dim 
	#echo $iters
	echo eigen $dim $iters
	./test-trqsq eigen $dim $iters 
        echo tcl $dim $iters
	./test-trqsq trqsq $dim $iters 
	echo "----------------------"
    done
done
