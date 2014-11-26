#include <stdio.h>
#include "minunit.h"
#include "Subheap.h"
#include "SubheapHandler.h"

int tests_run = 0;

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

static char * test_findHeapIndexBySize() {
	struct Subheap subheaps[4];
	
	fillSubheapBySize(&subheaps[0], 2);
	fillSubheapBySize(&subheaps[1], 6);
	fillSubheapBySize(&subheaps[2], 12);
	fillSubheapBySize(&subheaps[3], 24);
	
	mu_assert("First elem by -5", findHeapIndexBySize(subheaps, 4, -5) == 0);

	mu_assert("First elem by 0", findHeapIndexBySize(subheaps, 4, 0) == 0);

	mu_assert("First elem by 2", findHeapIndexBySize(subheaps, 4, 2) == 0);

	mu_assert("Second elem by 5", findHeapIndexBySize(subheaps, 4, 5) == 1);
	
	mu_assert("Second elem by 6", findHeapIndexBySize(subheaps, 4, 6) == 1);
	
	mu_assert("Third elem by 7", findHeapIndexBySize(subheaps, 4, 7) == 2);
	
	mu_assert("Third elem by 12", findHeapIndexBySize(subheaps, 4, 12) == 2);
	
	mu_assert("Four elem by 13", findHeapIndexBySize(subheaps, 4, 13) == 3);
	
	mu_assert("Four elem by 24", findHeapIndexBySize(subheaps, 4, 24) == 3);

	mu_assert("Post last elem by 25", findHeapIndexBySize(subheaps, 4, 25) == 4);
		
	return 0;
}

static char * test_findHeapIndexByPointer() {
	char heap[10];
	struct Subheap subheaps[4];
	
	fillSubheapByHeap(&subheaps[0], heap);
	fillSubheapByHeap(&subheaps[1], heap + 2);
	fillSubheapByHeap(&subheaps[2], heap + 4);
	fillSubheapByHeap(&subheaps[3], heap + 8);

	mu_assert("First elem by heap",  findHeapIndexByPointer(subheaps, 4, heap) == 0);

	mu_assert("First elem by heap + 1",  findHeapIndexByPointer(subheaps, 4, heap + 1) == 0);

	mu_assert("Second elem by heap + 2",  findHeapIndexByPointer(subheaps, 4, heap + 2) == 1);

	mu_assert("Second elem by heap + 3",  findHeapIndexByPointer(subheaps, 4, heap + 3) == 1);

	mu_assert("Third elem by heap + 4",  findHeapIndexByPointer(subheaps, 4, heap + 4) == 2);

	mu_assert("Four elem by heap + 8",  findHeapIndexByPointer(subheaps, 4, heap + 8) == 3);

	mu_assert("Four elem by heap + 20",  findHeapIndexByPointer(subheaps, 4, heap + 20) == 3);

	return 0;
}


static char * all_tests() {
    mu_run_test(test_findHeapIndexBySize);
    mu_run_test(test_findHeapIndexByPointer);

    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
