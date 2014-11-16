#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "MemoryManager.h"


int tests_run = 0;

static char * test_initHeap() {
    int heapsVariableSize[3] = {16000, 18000, 20000};
    int heapsVariablesCount[3] = {300, 10000, 11000};

    mu_assert("Should fail init cos' heaps count above max value", initHeap(12, heapsVariableSize, heapsVariablesCount) == -1);    
    mu_assert("Should fail init cos' heaps size above max value", initHeap(3, heapsVariableSize, heapsVariablesCount) == -1);    
    
    heapsVariableSize[0] = 2;
    heapsVariableSize[1] = 6;
    heapsVariableSize[2] = 10;
    
    heapsVariablesCount[0] = 20;
    heapsVariablesCount[1] = 18;
    heapsVariablesCount[2] = 10;
    
    mu_assert("Should correct init", initHeap(3, heapsVariableSize, heapsVariablesCount) == 1);   
    
    heapsVariableSize[0] = 20;
    heapsVariableSize[1] = 6;
    heapsVariableSize[2] = 10;
    
    mu_assert("Should fail init cos' heaps size isn't ascending", initHeap(3, heapsVariableSize, heapsVariablesCount) == -1);    
     
    return 0;
}

static char * all_tests() {
    mu_run_test(test_initHeap);
    
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
