#include <stdio.h>
#include "Configuration.h"
#include "SimpleCUnit.h"
#include "Subheap.h"
#include "MemoryManagerSubheap.h"


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

	variablesCount[0] = 1;
	assertTrue("Should five time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	assertTrue("Subheaps count should eq 4", 4 == getSubheapCount());

	char * heap = getHeap();
	char * toSubheapHeap = getSubheaps()[0].heap;
	char * toLastSubheapHeap = getSubheaps()[3].heap;
	
	assertTrue("First subheap's heap point to heap", toSubheapHeap == heap);		
	assertTrue("Last subheap should be heap + 1 + 2 + 3", heap + 1 + 2 + 3 == toLastSubheapHeap);
	assertTrue("Last byte should be heap + 1 + 2 + 3 + 4 - 1", heap + 1 + 2 + 3 + 4 - 1 == getLastByte());
	assertTrue("Last byte should be last subheap + 4 - 1", toLastSubheapHeap + 4 - 1 == getLastByte());
}

void test_allocate() {
	assertTrue("Should return NULL, cos' allocate -2", allocate(-2) == NULL);
	assertTrue("Should return NULL, cos' allocate 0", allocate(0) == NULL);	
	assertTrue("Should return NULL, cos' allocate 276447232", allocate(276447232) == NULL);
	
	char subheapsCount = 4;
	int variablesSize[4] = {2, 4, 8, 16};
	int variablesCount[4] = {3, 3, 3, 3};
	assertTrue("Should first time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	
	assertTrue("First var is eq heap", getHeap() == allocate(1));
	assertTrue("Second var is eq heap + 2", getHeap() + 2 == allocate(1));
	assertTrue("Third var is eq heap + 4", getHeap() + 4 == allocate(1));
	assertTrue("Four var is eq heap + 6", getHeap() + 6 == allocate(1));
	assertTrue("Five var is eq heap + 6 + 4", getHeap() + 10 == allocate(1));
	assertTrue("Six var (8) is eq heap + 2 * 3 + 4 * 3", getHeap() + 2 * 3 + 4 * 3 == allocate(8));
	assertTrue("Seven var (8) is eq heap + 2 * 3 + 4 * 3 + 8", getHeap() + 2 * 3 + 4 * 3 + 8 == allocate(8));
	assertTrue("Eight var (16) is eq heap + 2 * 3 + 4 * 3 + 8 * 3", getHeap() + 2 * 3 + 4 * 3 + 8 * 3 == allocate(16));
	assertTrue("Nine var (16) is eq heap + 2 * 3 + 4 * 3 + 8 * 3 + 16", getHeap() + 2 * 3 + 4 * 3 + 8 * 3 + 16 == allocate(16));
	assertTrue("Ten var (16) is eq heap + 2 * 3 + 4 * 3 + 8 * 3 + 16 * 2", getHeap() + 2 * 3 + 4 * 3 + 8 * 3 + 16 * 2 == allocate(16));
	assertTrue("Eleven var (16) can't be allocate, cos variables is full", NULL == allocate(16));
}

void test_remove() {	
	char subheapsCount = 4;
	int variablesSize[4] = {2, 4, 8, 16};
	int variablesCount[4] = {3, 3, 3, 3};
	assertTrue("Should first time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	
	char * heap = getHeap();
	
	assertTrue("Remove var invalid pointer exception, cos' below heap -1", VARIABLE_REMOVE_FAIL == removeVar(heap - 1));
	assertTrue("Remove var invalid pointer exception, cos' above last heap +1", VARIABLE_REMOVE_FAIL == removeVar(heap + 3 * (2 + 4 + 8 + 16)));
	assertTrue("Remove var valid, cos' heap", VARIABLE_REMOVE_SUCCESS == removeVar(heap));
	assertTrue("Remove var valid, cos' last byte", VARIABLE_REMOVE_SUCCESS == removeVar(heap + 3 * (2 + 4 + 8 + 16) - 1));
	
	char * variables = getVariables();
	variables[0] = 1;
	removeVar(heap);
	assertTrue("First var is empty", 0 == variables[0]);
	variables[3 + 3 + 3 + 3 - 1] = 1;
	removeVar(heap + 3 * (2 + 4 + 8 + 16) - 1);
	assertTrue("Last var is empty", 0 == variables[3 + 3 + 3 + 3 - 1]);	
}

int main(int argc, char **argv) {
    testSuit("Memory manager suit", 3,    
		initTestCase("Init case", &test_init),
		initTestCase("Allocate case", &test_allocate),
		initTestCase("Remove case", &test_remove));
    
    return 0;
}
