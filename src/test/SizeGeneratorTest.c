#include <stdio.h>
#include <stdlib.h>

#include "SimpleCUnit.h"
#include "SizeGenerator.h"


void test_getRange(){
	int count = 200;
	while (count--) {
		int val = getRange();
		assertTrue("Range should be between 16 and 16384", 16 <= val && val < 16384);
	}
}

int size = 6;
int fixArray[] = {16, 64, 256, 1024, 4 * 1024, 16 * 1024};

int isInsideArray(int * array, int arrSize, int value){
	while (arrSize--) 
		if (array[arrSize] == value)
			return 1;
	
	return 0;
}

void test_getFix(){
	int count = 200;
	while (count--)
		assertTrue("Fix should be inside {16, 64, 256, 1024, 4 * 1024, 16 * 1024}", isInsideArray (fixArray, size, getFix() ) );
}

int main(int argc, char **argv) {

	testSuit("Size generator test suit", 2, 
		initTestCase("Range test", &test_getRange),
		initTestCase("Fix test", &test_getFix)
		);

    return 0;
}
