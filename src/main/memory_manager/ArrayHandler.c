#include "ErrorCode.h"

int findFirstZero(char * array, int length){
	int index = 0;
	int result = ZERO_NOT_FOUND;
	
	for(; index < length; index++)
		if(0 == array[index]){
			result = index;
			break;
		}
		
	return result;	
}

void resetAllChars(char * array, int length){
	int index = 0;
	for(; index < length; index++)
		array[index] = 0;
}

long sumOfMulOfTwoArray(int * first, int * second, int length){
	long result = 0;
	
	int index = 0;
	for(; index < length; index++)
		result += first[index] * second[index];
	
	return result;
}

int sumOfArray(int * array, int length){
	int result = 0;
	
	int index = 0;
	for(; index < length; index++)
		result += array[index];
	
	return result;
}

char isAscending(int * array, int length){
	if (length != 1) {
		int index = 1;
		for(; index < length; index++)
			if(array[index] <= array[index - 1])
				return index;
	}	
	
	return ONLY_ACSENDING;
}

char isOnlyPositive(int * array, int length){
	int index = 0;
	for(; index < length; index++)
		if(array[index] <= 0)
			return index;
	
	return ONLY_POSITIVES;
}
