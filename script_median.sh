#!/bin/bash

make bin/median


echo "OpenCL"
for ((R=5; R<=50; R=R+5))
do
	echo $R
	for i in `seq 1 5`;
	do	
		./bin/median data/lena.png output.png $R OpenCL
	done
	echo
	echo
done


echo "OpenMP"
for ((R=5; R<=50; R=R+5))
do
	echo $R
	for i in `seq 1 5`;
	do	
		./bin/median data/lena.png output.png $R OpenMP
	done
	echo
	echo
done


echo "CPU"
for ((R=5; R<=50; R=R+5))
do
	echo $R
	for i in `seq 1 5`;
	do	
		./bin/median data/lena.png output.png $R CPU
	done
	echo
	echo
done
