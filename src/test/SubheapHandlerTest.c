#include <stdio.h>
#include "SimpleCUnit.h"
#include "Subheap.h"
#include "SubheapHandler.h"


void fillSubheap(Subheap* subheap, char* variables, int variablesCount, int variablesSize, char* heap) {
    subheap->variables = variables;
    subheap->variablesCount = variablesCount;
    subheap->variablesSize = variablesSize;
    subheap->heap = heap;
}

void fillSubheapBySize(Subheap* subheap, int variablesSize) {
    fillSubheap(subheap, NULL, 0, variablesSize, NULL);
}

void fillSubheapByHeap(Subheap* subheap, char* heap) {
    fillSubheap(subheap, NULL, 0, 0, heap);
}

void test_findHeapIndexBySize() {
    Subheap subheaps[4];

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
    Subheap subheaps[4];

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

    assertTrue("Four elem by heap + 20 (!!!) it's over heap array",  findHeapIndexByPointer(subheaps, 4, heap + 20) == 3);
}

void test_initSubheaps() {
    char heap[10] = {'l'};
    char variables[5];

    Subheap subheaps[3];

    char subheapCount = 3;

    int variablesSize[3] = {1, 2, 3};
    int variablesCount[3] = {1, 2, 1};

    assertTrue("initSubheaps should eq 6", 8 == initSubheaps(subheaps, subheapCount, variables, heap, variablesSize, variablesCount));

    assertTrue("Should eq point heap == subheaps[0].heap", heap == subheaps[0].heap);
    assertTrue("First heap's byte == 'l'", 'l' == (char) *heap);
    assertTrue("First subheap's heap's byte should eq 'l' and first heap's byte", (char) *heap == (char) *subheaps[0].heap);
    assertTrue("Should eq point heap + 1 == subheaps[1].heap", heap + 1 == subheaps[1].heap);
    assertTrue("Should eq point heap + 1 + 4 == subheaps[2].heap", heap + 1 + 4 == subheaps[2].heap);

    assertTrue("Variables of first subheap should point to first variables", variables == subheaps[0].variables);
    assertTrue("Variables of second subheap point to first variables + 1", variables + 1 == subheaps[1].variables);
    assertTrue("Variables of third subheap point to first variables + 3", variables + 1 + 2 == subheaps[2].variables);

    assertTrue("First size is 1", 1 == subheaps[0].variablesSize);
    assertTrue("Second size is 2", 2 == subheaps[1].variablesSize);
    assertTrue("Third size is 3", 3 == subheaps[2].variablesSize);

    assertTrue("First vars count is 1", 1 == subheaps[0].variablesCount);
    assertTrue("Second vars count is 2", 2 == subheaps[1].variablesCount);
    assertTrue("Third vars count is 1", 1 == subheaps[2].variablesCount);
}

int main(int argc, char** argv) {
    testSuit("Subheap handler suit", 3,
	     initTestCase("Find heap's index by size", &test_findHeapIndexBySize),
	     initTestCase("Init subheaps", &test_initSubheaps),
	     initTestCase("Find heap's index by pointer", &test_findHeapIndexByPointer));

    return 0;
}
