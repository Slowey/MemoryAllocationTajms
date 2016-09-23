#!/bin/sh

declare totalTests=4;
declare testToRun=1;
declare numberOfObjects=1; #starts on this and then increments it each run by 2
declare increment=2; # multiplier
declare maxNumberOfInts=10000000;
declare perTestRuns=10;
declare testRun=1;

while [ $testToRun -le $totalTests ]
do
	numberOfObjects=1;
	while [ $numberOfObjects -lt $maxNumberOfInts ]
	do
		testRun=0;
		while [ $testRun -lt $perTestRuns ]
		do
			declare seedNumber=$RANDOM;
			#RUN
			( cd ReleaseOwn/; ./MemoryAllocationApp.exe --test $testToRun --num $numberOfObjects --seed $seedNumber)
			( cd ReleaseOs/; ./MemoryAllocationApp.exe --test $testToRun --num $numberOfObjects --seed $seedNumber)
			#Increment
			((testRun++));
		done
		numberOfObjects=$((numberOfObjects * increment));
	done
	testToRun=$((testToRun+1));
	
done