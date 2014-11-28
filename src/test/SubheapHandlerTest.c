#include <stdio.h>
#include "SimpleCUnit.h"
#include "Subheap.h"
#include "SubheapHandler.h"


void fillSubheap(struct Subheap * subheap, char * variables, int variablesCount, int variablesSize, char * heap){
	subheap->variables = variables;
	subheap->variablesCount = variablesCount;
	subheap->variablesSize = variablesSize;
	subheap->heap = heap;
}

void fillSubheapBySize(struct Subheap * subheap, int variablesSize){
	fillSubheap(subheap, NULL, 0, variablesSize, NULL);
}

void fillSubheapByHeap(struct Subheap * subheap, char * heap){
	fillSubheap(subheap, NULL, 0, 0, heap);
}

void test_findHeapIndexBySize() {
	struct Subheap subheaps[4];
	
	fillSubheapBySize(&subheaps[0], 2);
	fillSubheapBySize(&subheaps[1], 6);
	fillSubheapBySize(&subheaps[2], 12);
	fillSubheapBySize(&subheaps[3], 24);
	
	assertTrue("First elem by -5", findHeapIndexBySize(subheaps, 4, -5) == 0);

	assertTrue("First elem by 0", findHeapIndexBySize(subheaps, 4, 0) == 0);

	assertTrue("First elem by 2", findHeapIndexBySize(subheaps, 4, 2) == 0);

	assertTrue("Second elem by 5", findHeapIndexBySize(subheaps, 4, 5) == 1);
	
	assertTrue("Second elem by 6", findHeapIndexBySize(subheaps, 4, 6) == 1);
	
	assertTrue("Third elem by 7", findHeapIndexBySize(subheaps, 4, 7) == 2);
	
	assertTrue("Third elem by 12", findHeapIndexBySize(subheaps, 4, 12) == 2);
	
	assertTrue("Four elem by 13", findHeapIndexBySize(subheaps, 4, 13) == 3);
	
	assertTrue("Four elem by 24", findHeapIndexBySize(subheaps, 4, 24) == 3);

	assertTrue("Post last elem by 25", findHeapIndexBySize(subheaps, 4, 25) == 4);
}

void test_findHeapIndexByPointer() {
	char heap[10];
	struct Subheap subheaps[4];
	
	fillSubheapByHeap(&subheaps[0], heap);
	fillSubheapByHeap(&subheaps[1], heap + 2);
	fillSubheapByHeap(&subheaps[2], heap + 4);
	fillSubheapByHeap(&subheaps[3], heap + 8);

	assertTrue("First elem by heap",  findHeapIndexByPointer(subheaps, 4, heap) == 0);

	assertTrue("First elem by heap + 1",  findHeapIndexByPointer(subheaps, 4, heap + 1) == 0);

	assertTrue("Second elem by heap + 2",  findHeapIndexByPointer(subheaps, 4, heap + 2) == 1);

	assertTrue("Second elem by heap + 3",  findHeapIndexByPointer(subheaps, 4, heap + 3) == 1);

	assertTrue("Third elem by heap + 4",  findHeapIndexByPointer(subheaps, 4, heap + 4) == 2);

	assertTrue("Four elem by heap + 8",  findHeapIndexByPointer(subheaps, 4, heap + 8) == 3);

	assertTrue("Four elem by heap + 20",  findHeapIndexByPointer(subheaps, 4, heap + 20) == 3);
}

int main(int argc, char **argv) {
	testSuit("Subheap handler suit", 2,
		initTestCase("Find heap's index by size", &test_findHeapIndexBySize),
		initTestCase("Find heap's index by pointer", &test_findHeapIndexByPointer));

    return 0;
}
