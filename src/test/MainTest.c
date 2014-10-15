#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "ArrayHandler.h"
 
 int tests_run = 0;
 
 
 static char * test_getHeapIndex() {
     int heapsCount = 4;
     long heapsSize[] = {2, 3, 6, 10};
     mu_assert("Should find index of last heap, by max value", getHeapIndex(heapsSize, heapsCount, 10) == 3);
     mu_assert("Should be incorrect (-1), cos' value above max heap's size", getHeapIndex(heapsSize, heapsCount, 11) == -1);
     mu_assert("Should find firts heap, cos' min value", getHeapIndex(heapsSize, heapsCount, 1) == 0);
     mu_assert("Should find not maximum size", getHeapIndex(heapsSize, heapsCount, 5) == 2);
     return 0;
 }
 
 static char * test_findAndSetFreeVarribleIndex() {
     int offsetInsideVarribles[] = {3, 3, 4};
          
     char varribles[10] = {0, 1, 0/*First*/, 1, 1, 1/*Second*/, 1, 0};
     mu_assert("Should find first index in first heap", findAndSetFreeVarribleIndex(varribles, offsetInsideVarribles[0]) == 0);
     
     mu_assert("Should find last index in first heap", findAndSetFreeVarribleIndex(varribles, offsetInsideVarribles[0]) == 2);
     
     
     mu_assert("Shouldn't find in second heap", findAndSetFreeVarribleIndex(&varribles[offsetInsideVarribles[0]], offsetInsideVarribles[1]) == -1);
 
     mu_assert("Shouldn't find in last heap", findAndSetFreeVarribleIndex(&varribles[offsetInsideVarribles[0] + offsetInsideVarribles[1]], offsetInsideVarribles[2]) == 1); 
     
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
    long heapSize = 100;
    char heap[100] = {0};
    int heapsCount = 5;
    int countVarribleInsidHeap[5] = {3, 3};
    long heapsSize[5] = {2, 4, 8, 16, 32};
    long heapsAddress[5] = {0};
    heapsAddress[0] = (long)heap;
    heapsAddress[1] = (long)heap + heapsSize[0] * countVarribleInsidHeap[0];

    int offsetVarribles[5] = {0};
    offsetVarribles[1] = 3;
    char varribles[100] = {0};  
    long size = 1;
    
    char* ptr = getPointer(heap, heapsCount, heapsSize, heapsAddress, offsetVarribles, countVarribleInsidHeap, varribles, size);
    
    *ptr = 'a';
    mu_assert("Should ptr eq a", *ptr == 'a');
    mu_assert("Should heap 0 eq a", heap[0] == 'a');
    
    ptr = getPointer(heap, heapsCount, heapsSize, heapsAddress, offsetVarribles, countVarribleInsidHeap, varribles, size);
    *ptr = 's';
    mu_assert("Should ptr eq s", *ptr == 's');
    mu_assert("Should heap 1 eq s", heap[2] == 's');
    
    size = 3;
    ptr = getPointer(heap, heapsCount, heapsSize, heapsAddress, offsetVarribles, countVarribleInsidHeap, varribles, size);
    *ptr = 'z';
    mu_assert("Should ptr eq z", *ptr == 'z');
    mu_assert("Should heap 6 eq z", heap[6] == 'z');
    
    size = 4;
    int * ptrI = ( int * )getPointer(heap, heapsCount, heapsSize, heapsAddress, offsetVarribles, countVarribleInsidHeap, varribles, size);
    *ptrI = 25;
    int ptrI2 = heap[10];
    mu_assert("Should ptr int eq 25", *ptrI == 25);
    mu_assert("Should heap 10 eq 25", ptrI2 == 25);
    
    size = 33;
    char * ptrI3 = getPointer(heap, heapsCount, heapsSize, heapsAddress, offsetVarribles, countVarribleInsidHeap, varribles, size);
    mu_assert("Should be null", ptrI3 == NULL);
    
    return 0;
}
 
 static char * all_tests() {
     mu_run_test(test_getHeapIndex);
     mu_run_test(test_findAndSetFreeVarribleIndex);
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
