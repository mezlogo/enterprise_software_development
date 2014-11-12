#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "ArrayHandler.h"


int tests_run = 0;

static char * test_findHeapIndexBySize() {
    int heapsCount = 4;
    long heapsSize[] = {2, 3, 6, 10};
    mu_assert("Should find index of last heap, by max value", findHeapIndexBySize(heapsSize, heapsCount, 10) == 3);
    //mu_assert("Should be incorrect (-1), cos' value above max heap's size", findHeapIndexBySize(heapsSize, heapsCount, 11) == -1);
    mu_assert("Should find firts heap, cos' min value", findHeapIndexBySize(heapsSize, heapsCount, 1) == 0);
    mu_assert("Should find not maximum size", findHeapIndexBySize(heapsSize, heapsCount, 5) == 2);
    return 0;
}

static char * test_findAndSetVariableIndex() {
    int variblesCount = 10;
    char varibles [10] = {0};
    mu_assert("Should return first varibles index and set 1", findAndSetVariableIndex(varibles, variblesCount) == 0 && varibles[0] == 1);

    mu_assert("Should return last varibles, by 9 offset varybles, index and set 1", findAndSetVariableIndex(varibles + 9, 1) == 0 && varibles[9] == 1);

    mu_assert("Should return error, cos' last var isn't empty, by offset 9", findAndSetVariableIndex(varibles + 9, 1) == -1 && varibles[9] == 1);

    mu_assert("Should return 8 varibles index and set 1", findAndSetVariableIndex(varibles + 8, 2) == 0 && varibles[8] == 1);

    mu_assert("Should return error, cos' no one empty var found by offset 8", findAndSetVariableIndex(varibles + 8, 2) == -1 && varibles[8] == 1);

    return 0;
}

static char * test_isAscendingOrder() {
    int heapCount = 4;
    int heapSize [4] = {1, 3, 4, 5};

    mu_assert("Should return -1 cos' ascending", isAscendingOrder(heapSize, heapCount) == -1);

    heapSize[0] = 0;

    mu_assert("Should return 0 cos' first is zero", isAscendingOrder(heapSize, heapCount) == 0);

    heapSize[0] = 1;
    heapSize[2] = 2;

    mu_assert("Should return 2 cos' third is below that second element", isAscendingOrder(heapSize, heapCount) == 2);

    return 0;
}

static char * test_findHeapIndexByPointer() {
    char heap[12] = {1};

    char* heapsAddress[3] = {0};
    heapsAddress[0] = (void*) heap;
    heapsAddress[1] = (void*) heap + 6;

    heapsAddress[2] = (void*) heapsAddress[1] + 3;

    heap[6] = 5;
    heap[9] = 2;

    mu_assert("First elem of char should be 1 and eq", heap[0] == 1 && heap[0] == *heapsAddress[0]);

    mu_assert("Should eq ptr", (void*) heap == heapsAddress[0]);

    mu_assert("Sixth elem of char should be 5 and eq", heap[6] == 5 && heap[6] == *heapsAddress[1]);

    mu_assert("Ninth elem of char should be 2 and eq", heap[9] == 2 && heap[9] == *heapsAddress[2]);

    mu_assert("Ptr to head of heap, should return 0", findHeapIndexByPointer(heapsAddress, 3, heap) == 0);

    mu_assert("Ptr to last byte of first heap, should return 0", findHeapIndexByPointer(heapsAddress, 3, (char*) heap + 5) == 0);

    mu_assert("Ptr to sixth byte of heap, should return 0", findHeapIndexByPointer(heapsAddress, 3, (char*) heap + 6) == 1);

    mu_assert("Ptr to first byte of last heap, should return 2", findHeapIndexByPointer(heapsAddress, 3, (char*) heap + 9) == 2);

    mu_assert("Ptr to invalid byte above of whole heap, should return 2, cos' last heap index", findHeapIndexByPointer(heapsAddress, 3, (char*) heap + 200) == 2);

    return 0;
}

static char * test_sumOfHeapByVarCountAndSize() {
    int heapsSize[3] = {2, 4, 10};
    int heapsVariables[3] = {6, 4, 2};

    mu_assert("Should return correct 48 like mul 2 * 6 + 4 * 4 + 10 * 2", sumOfHeapByVarCountAndSize(heapsSize, heapsVariables, 3) == 48);

    heapsSize[2] = 0;

    mu_assert("Should return incorrect -1 cos' last heap size is zero", sumOfHeapByVarCountAndSize(heapsSize, heapsVariables, 3) == -1);

    heapsSize[2] = 10;
    heapsVariables[2] = -5;

    mu_assert("Should return incorrect -1 cos' last heap variable count is -5", sumOfHeapByVarCountAndSize(heapsSize, heapsVariables, 3) == -1);

    return 0;
}

static char * test_initHeapsAddress() {
    char heap[48] = {0};
    int heapsSize[3] = {2, 4, 10};
    int heapsVariables[3] = {6, 4, 2};
    char* heapsAddress[3] = {};

    mu_assert("Should init heaps address", initHeapsAddress(heapsAddress, heap, heapsSize, heapsVariables, 3) == 1);
    
    mu_assert("First heaps address ptr heap", heapsAddress[0] == heap);
    mu_assert("Second heaps address ptr heap + 2 * 6", heapsAddress[1] == heap + 12);
    mu_assert("Third heaps address ptr heap + 2 * 6 + 4 * 4", heapsAddress[2] == heap + 28);
    
    *heapsAddress[2] = '$';
    mu_assert("First var in last heap should eq '$'", heap[28] == '$');
    
    return 0;
}



static char * test_initHeapsVariables() {
    int heapsVariables[3] = {6, 4, 2};
    char variables[12] = {0};
    char* heapsAddressVariables[3] = {};
    
    mu_assert("Should init heaps variables", initHeapsVariables(heapsAddressVariables, variables, heapsVariables, 3) == 1);
    mu_assert("First heaps var ptr vars", heapsAddressVariables[0] == variables);
    mu_assert("Second heaps var ptr vars + 6", heapsAddressVariables[1] == variables + 6);
    mu_assert("Third heaps var ptr vars + 10", heapsAddressVariables[2] == variables + 10);
    
    *heapsAddressVariables[2] = 1;
    mu_assert("First var in last heap should eq 1", variables[10] == 1);
    
    return 0;
}

static char * all_tests() {
    mu_run_test(test_findHeapIndexBySize);
    mu_run_test(test_findAndSetVariableIndex);
    mu_run_test(test_isAscendingOrder);
    mu_run_test(test_findHeapIndexByPointer);
    mu_run_test(test_sumOfHeapByVarCountAndSize);
    mu_run_test(test_initHeapsAddress);
    mu_run_test(test_initHeapsVariables);
    
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
