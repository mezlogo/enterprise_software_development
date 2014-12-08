#include <stdio.h>
#include "Configuration.h"

unsigned long allocateIndex;
unsigned long removeIndex;

unsigned long allocateMeasuring[ITERATION_COUNT];
unsigned long removeMeasuring[ITERATION_COUNT];

void reset() {
	allocateIndex = 0;
	removeIndex = 0;
}

void logAllocate(unsigned long time) {
	allocateMeasuring[allocateIndex++] = time;
}

void logRemove(unsigned long time) {
	removeMeasuring[removeIndex++] = time;
}

void printArray(unsigned long * array, long length) {
	long index = 0;
	for (; index < length; index++) printf("%lu ", array[index]);
}

unsigned long sum(unsigned long * array, long length) {
	unsigned long result = 0;
	long index = 0;

	for (; index < length; index++) 
		result += array[index];
	
	return result;
}

unsigned long min(unsigned long * array, long length) {
	unsigned long result = array[0];
	long index = 0;

	for (; index < length; index++) 
		if (array[index] < result) 
			result = array[index];
	
	return result;
}

unsigned long max(unsigned long * array, long length) {
	unsigned long result = array[0];
	long index = 0;

	for (; index < length; index++) 
		if (result < array[index]) 
			result = array[index];
	
	return result;
}

void printMeasuring(unsigned long * array, long length, char * measuringName) {
	printf("\n%s%s%lu\n", measuringName, "\nCount: ", length);
	printArray(array, length);
	printf("%s%lu%s%lu%s%lu\n", "\nMin: ", min(array, length), "\nMax: ", max(array, length), "\nAvg: ", sum(array, length) / length);
}

void show() {
	printMeasuring(allocateMeasuring, allocateIndex, "Allocate time: ");
	printMeasuring(removeMeasuring, removeIndex, "Remove time: ");
}
