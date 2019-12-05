#!/bin/bash

make bin/dotproduct




echo "CPU"
for j in `seq 3 7`
do
	let "N = 10 ** $j"
	echo $N
	for i in `seq 1 5`;
	do	
		
		./bin/dotproduct $N CPU
	done
	echo
	echo
done

echo "OpenCL"
for j in `seq 3 7`
do
	let "N = 10 ** $j"
	echo $N
	for i in `seq 1 5`;
	do	
		
		./bin/dotproduct $N OpenCL
	done
	echo
	echo
done

echo "OpenMP"
for j in `seq 3 7`
do
	let "N = 10 ** $j"
	echo $N
	for i in `seq 1 5`;
	do	
		
		./bin/dotproduct $N OpenMP
	done
	echo
	echo
done

