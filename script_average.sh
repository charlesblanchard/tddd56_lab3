#!/bin/bash

make bin/average


echo "CPU"
echo

echo 2
for i in `seq 1 5`;
do	
	./bin/average data/lena.png output.png 2 CPU
done
echo

for ((R=5; R<=50; R=R+5))
do
	echo $R
	for i in `seq 1 5`;
	do	
		./bin/average data/lena.png output.png $R CPU
	done
	echo
done

echo "OpenCL"

echo 2
for i in `seq 1 5`;
do	
	./bin/average data/lena.png output.png 2 OpenCL
done
echo

for ((R=5; R<=50; R=R+5))
do
	echo $R
	for i in `seq 1 5`;
	do	
		./bin/average data/lena.png output.png $R OpenCL
	done
	echo
done

echo "OpenMP"
echo

echo 2
for i in `seq 1 5`;
do	
	./bin/average data/lena.png output.png 2 OpenMP
done
echo

for ((R=5; R<=50; R=R+5))
do
	echo $R
	for i in `seq 1 5`;
	do	
		./bin/average data/lena.png output.png $R OpenMP
	done
	echo
done

