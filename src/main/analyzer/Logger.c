#include <stdio.h>
#include <string.h>
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
	if (LOGGER_SIZE < primaryIndex) { printf("%s", "Primary logger is out of range!\n"); return; }
	primaryMeasuring[primaryIndex++] = time;
}

void logSecondary(unsigned long time) {
	if (LOGGER_SIZE < secondaryIndex) { printf("%s", "Secondary logger is out of range!\n"); return; }
	secondaryMeasuring[secondaryIndex++] = time;
}

void printArray(unsigned long* array,
				long length) {
	long index = 0;

	for (; index < length; index++) { printf("%lu ", array[index]); }
}

unsigned long sum(unsigned long* array,
				  long length) {
	unsigned long result = 0;
	long index = 0;

	for (; index < length; index++)
	{ result += array[index]; }

	return result;
}

unsigned long min(unsigned long* array,
				  long length) {
	unsigned long result = array[0];
	long index = 0;

	for (; index < length; index++)
		if (array[index] < result)
		{ result = array[index]; }

	return result;
}

unsigned long max(unsigned long* array,
				  long length) {
	unsigned long result = array[0];
	long index = 0;

	for (; index < length; index++)
		if (result < array[index])
		{ result = array[index]; }

	return result;
}

void fileLoggerOutput(char* name, unsigned long* array, unsigned long length, char* measuringName,
					  unsigned long maxValue, unsigned long averageValue, unsigned long minValue) {
	FILE* file;
#define fileNameLength 80
	char fileName[fileNameLength];
	sprintf(fileName, "%s [%s] (%lu, %lu, %lu) %lu.txt", name, measuringName, minValue, averageValue,
			maxValue, length);
	file = fopen(fileName, "wb");

	if (NULL == file) {
		printf("%s:%s\n", "Can't create file ", fileName);
		return;
	}

	int index = 0;

	for (; index < length; index++) {fprintf(file, "%lu ", array[index]); }

	fclose(file);
}

void consoleLoggerOutput(char* name, unsigned long* array,	unsigned long length,
						 char* measuringName, unsigned long maxValue, unsigned long averageValue, unsigned long minValue)  {
	printf("\n%s%s%lu\n", measuringName, "\nCount: ", length);
	printArray(array, length);
	printf("%s%lu%s%lu%s%lu\n", "\nMin: ", minValue, "\nMax: ", maxValue, "\nAvg: ", averageValue);
}

void (*showMeasure)(char* name, unsigned long* array,	unsigned long length, char* measuringName,
					unsigned long maxValue, unsigned long averageValue, unsigned long minValue) = &consoleLoggerOutput;

void setShowMeasure(void (*_showMeasure)(char* name, unsigned long* array,	unsigned long length,
					char* measuringName, unsigned long maxValue, unsigned long averageValue, unsigned long minValue)) {
	showMeasure = _showMeasure;
}

void setFileLoggerOutput() { showMeasure = &fileLoggerOutput; }

void show(char* name) {
#define calcAndShow(name, array, length, measuringName) showMeasure(name, array, length, measuringName, max(array, length), sum(array, length) / (0 == length ? 1 : length), min(array,	length))
	calcAndShow(name, primaryMeasuring, primaryIndex, "Primary time: ");
	calcAndShow(name, secondaryMeasuring, secondaryIndex, "Secondary time: ");
}


