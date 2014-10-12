#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
 
 int tests_run = 0;
 
 
 static char * test_getHeapIndex() {
     int heapsCount = 4;
     int heapsSize[] = {2, 3, 6, 10};
     mu_assert("Should find index of last heap, by max value", getHeapIndex(heapsSize, heapsCount, 10) == 3);
     mu_assert("Should be incorrect (-1), cos' value above max heap's size", getHeapIndex(heapsSize, heapsCount, 11) == -1);
     mu_assert("Should find firs heap, cos' min value", getHeapIndex(heapsSize, heapsCount, 1) == 0);
     mu_assert("Should find not maximum size", getHeapIndex(heapsSize, heapsCount, 5) == 2);
     return 0;
 }
 
 static char * test_findSetFreeVarribleIndex() {
     int offsetInsideVarribles[] = {3, 3, 4};
          
     char varribles[10] = {0, 1, 0/*First*/, 1, 1, 1/*Second*/, 1, 0};
     mu_assert("Should find first index in first heap", findSetFreeVarribleIndex(varribles, offsetInsideVarribles[0]) == 0);
     
     mu_assert("Should find last index in first heap", findSetFreeVarribleIndex(varribles, offsetInsideVarribles[0]) == 2);
     
     
     mu_assert("Shouldn't find in second heap", findSetFreeVarribleIndex(&varribles[offsetInsideVarribles[0]], offsetInsideVarribles[1]) == -1);
 
     mu_assert("Shouldn't find in last heap", findSetFreeVarribleIndex(&varribles[offsetInsideVarribles[0] + offsetInsideVarribles[1]], offsetInsideVarribles[2]) == 1); 
     
     return 0;
 }
 
 
 
 static char * test_sumOfCharArray() {
     int array[] = {3, 10, 5};
     mu_assert("Should correct find sum", sumOfArray(array, 1) == 3);
     mu_assert("Should correct find sum", sumOfArray(array, 2) == 13);
     mu_assert("Should correct find sum", sumOfArray(array, 3) == 18);
     mu_assert("Should incorrect find sum", sumOfArray(array, 1) != 0);
     
     
     return 0;
 }
 
  
 static char * test_getPointer() {
     int heapSize = 100;
     int heap[100] = {0};
     int heapsCount = 5;
     int heapsSize[5] = {2, 4, 8, 16, 32};
     long heapsAddress[5] = {0};
     heapsAddress[0] = (long)heap;
     
     printf("Heap: %lu\n", (long)heap);
     
     int offsetVarribles[5] = {0};
     int countVarribleInsidHeap[5] = {3};
     char varribles[100] = {0};
     int size = 1;
     
     printf("Var: %d\n", varribles[0]);
          
     long s = getPointer(heap, heapsCount, heapsSize, heapsAddress, offsetVarribles, countVarribleInsidHeap, varribles, size);
     
     //mu_assert("Lol", heap == s);
     
     printf("Var: %d\n", varribles[0]);
     printf("Heap: %lu\n", (long)&s);
     
     
     return 0;
 }
 
 static char * all_tests() {
     mu_run_test(test_getHeapIndex);
     mu_run_test(test_findSetFreeVarribleIndex);
     mu_run_test(test_sumOfCharArray);
     mu_run_test(test_getPointer);
    
     return 0;
 }
 
 int main(int argc, char **argv) {
     char *result = all_tests();
     if (result != 0) {
         printf("%s\n", result);
     }
     else {
         printf("ALL TESTS PASSED\n");
     }
     printf("Tests run: %d\n", tests_run);
 
     return result != 0;
 }
