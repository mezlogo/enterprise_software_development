#include <stdio.h>
#include "Configuration.h"

unsigned long primaryIndex;
unsigned long secondaryIndex;

unsigned long primaryMeasuring[LOGGER_SIZE];
unsigned long secondaryMeasuring[LOGGER_SIZE];

void reset() {
    primaryIndex = 0;
    secondaryIndex = 0;
}

void logPrimary(unsigned long time) {
    primaryMeasuring[primaryIndex++] = time;
}

void logSecondary(unsigned long time) {
    secondaryMeasuring[secondaryIndex++] = time;
}

void printArray(unsigned long* array, long length) {
    long index = 0;
    for (; index < length; index++) { printf("%lu ", array[index]); }
}

unsigned long sum(unsigned long* array, long length) {
    unsigned long result = 0;
    long index = 0;

    for (; index < length; index++)
    { result += array[index]; }

    return result;
}

unsigned long min(unsigned long* array, long length) {
    unsigned long result = array[0];
    long index = 0;

    for (; index < length; index++)
	if (array[index] < result)
	{ result = array[index]; }

    return result;
}

unsigned long max(unsigned long* array, long length) {
    unsigned long result = array[0];
    long index = 0;

    for (; index < length; index++)
	if (result < array[index])
	{ result = array[index]; }

    return result;
}

void printMeasuring(unsigned long* array, unsigned long length, char* measuringName) {
    printf("\n%s%s%lu\n", measuringName, "\nCount: ", length);
    printArray(array, length);
    printf("%s%lu%s%lu%s%lu\n", "\nMin: ", min(array, length), "\nMax: ", max(array, length), "\nAvg: ", sum(array, length) / length);
}

void show() {
    printMeasuring(primaryMeasuring, primaryIndex, "Primary time: ");
    printMeasuring(secondaryMeasuring, secondaryIndex, "Secondary time: ");
}
