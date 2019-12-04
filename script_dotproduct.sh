#!/bin/bash

make bin/dotproduct

echo
echo
echo CPU
echo


for i in `seq 1 10`;
do	
	./bin/dotproduct 100 CPU
done

echo
echo
echo OpenMP
echo

for i in `seq 1 10`;
do	
	./bin/dotproduct 100 OpenMP
done

echo
echo
echo OpenCL
echo


echo "CPU"
for j in `seq 1 9`
do
	for i in `seq 1 10`;
	do	
		let "N = 2 * $j"
		./bin/dotproduct $N CPU
	done
done

echo
echo

echo "OpenCL"
for j in `seq 1 9`
do
	for i in `seq 1 10`;
	do	
		let "N = 2 * $j"
		./bin/dotproduct $N OpenCL
	done
done

echo
echo

echo "OpenMP"
for j in `seq 1 9`
do
	for i in `seq 1 10`;
	do	
		let "N = 10 * $j"
		./bin/dotproduct $N OpenMP
	done
done

echo
echo
