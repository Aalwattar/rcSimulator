#!/bin/bash

for File in $(cat "$1")
do
	# uniform from 8-12	
	# non uniform from 13- 17

	for arch in {8..12}
do
	 echo -e "\n\nBenchmark  $File PRR_$((arch-8)) \n "
#	./SchedSim -s $arch  --dfg-file ~/SharedDrive/conf/dfgs/${File} --scheduler $2 
done 
#ls -l $(basename $File)
#echo ~/SharedDrive/conf/dfgs/${File} 
done
