#include <stdio.h>
#include "ErrorCode.h"
#include "SimpleCUnit.h"
#include "Subheap.h"
#include "MemoryManagerDevelop.h"


void test_init() {
	char subheapsCount = 4;
	int variablesSize[4] = {1, 2, 3, 4};
	int variablesCount[4] = {1, 1, 1, 1};
	
	assertTrue("Should first time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	assertTrue("Shouldn't init cos' subheap count -1", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, -1));
	assertTrue("Shouldn't init cos' subheap count 0", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, 0));
	assertTrue("Shouldn't init cos' subheap count 100000", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, 100000));
	
	assertTrue("Should second time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	variablesSize[2] = 1;
	assertTrue("Shouldn't init cos' variablesSize[2] = 1, isn't ascending", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, subheapsCount));
	
	variablesSize[2] = 3;
	assertTrue("Should third time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	variablesSize[0] = -21;
	assertTrue("Shouldn't init cos' variablesSize[0] = -1, isn't only positive", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, subheapsCount));
	
	variablesSize[0] = 1;
	assertTrue("Should four time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	variablesCount[0] = -1;
	assertTrue("Shouldn't init cos' variablesCount[0] = -1, isn't only positive", INITIAL_INPUT_PARAMS_ERROR ==init(variablesSize, variablesCount, subheapsCount));
}

void test_allocate() {
	assertTrue("Should return NULL, cos' allocate -2", allocate(-2) == NULL);
	
	assertTrue("Should return NULL, cos' allocate 0", allocate(0) == NULL);
	
	assertTrue("Should return NULL, cos' allocate 276447232", allocate(276447232) == NULL);
}

void test_remove() {
	
}

int main(int argc, char **argv) {
    testSuit("Memory manager suit", 3,    
		initTestCase("Init case", &test_init),
		initTestCase("Allocate case", &test_allocate),
		initTestCase("Remove case", &test_remove));
    
    return 0;
}
