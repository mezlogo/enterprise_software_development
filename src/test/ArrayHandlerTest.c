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
 /*
 static char * test_findAndSetFreeVarribleIndex() {
     int offsetInsideVarribles[] = {3, 3, 4};
          
     char varribles[10] = {0, 1, 0        , 1, 1, 1          ,  1, 0};
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
 
 static char * test_removePointer() {
    long heapSize = 100;
    char heap[100] = {0};
    int heapsCount = 5;
    int countVarribleInsidHeap[5] = {3, 3};
    long heapsSize[5] = {2, 4, 8, 16, 32};
    long heapsAddress[5] = {0};
    heapsAddress[0] = (long)heap;
    heapsAddress[1] = heapsAddress[0] + heapsSize[0] * countVarribleInsidHeap[0];
    heapsAddress[2] = heapsAddress[1] + heapsSize[1] * countVarribleInsidHeap[1];
    
    void** heapsAddressPtr = (void**) heapsAddress;
    
    int offsetVarribles[5] = {0};
    offsetVarribles[1] = 3;
    char varribles[100] = {1, 1, 0, 1, 1, 0};  

    void* pointerToRemove= (void*) heap;
    int res = removePointer(pointerToRemove, heapsCount, heapsSize, heapsAddressPtr, offsetVarribles, varribles, heapSize);
    
    mu_assert("Should return 0", res == 0);
    mu_assert("Should set first var to zero", varribles[0] == 0);
    mu_assert("Should be 1, before remove", varribles[1] == 1);
    
    pointerToRemove= (void*) (heap + 2);
    res = removePointer(pointerToRemove, heapsCount, heapsSize, heapsAddressPtr, offsetVarribles, varribles, heapSize);
    
    mu_assert("Should return 0, removing second var", res == 0);
    mu_assert("Should second var eq 0", varribles[1] == 0);
    
    pointerToRemove= (void*) (heap + 2*3);
    res = removePointer(pointerToRemove, heapsCount, heapsSize, heapsAddressPtr, offsetVarribles, varribles, heapSize);
    mu_assert("Should return 0, removing four var", res == 0);
    mu_assert("Should four var eq 0", varribles[3] == 0);
      
    pointerToRemove= (void*) (heap + 2*3 + 4);
    res = removePointer(pointerToRemove, heapsCount, heapsSize, heapsAddressPtr, offsetVarribles, varribles, heapSize);
    mu_assert("Should return 0, removing five var", res == 0);
    mu_assert("Should five var eq 0", varribles[4] == 0);
   
    pointerToRemove= (void*) (heap - 10);
    res = removePointer(pointerToRemove, heapsCount, heapsSize, heapsAddressPtr, offsetVarribles, varribles, heapSize);
    mu_assert("Should return -1, removing pre heap address", res == -1);
    
    pointerToRemove= (void*) (heap + heapSize + 10);
    res = removePointer(pointerToRemove, heapsCount, heapsSize, heapsAddressPtr, offsetVarribles, varribles, heapSize);
    mu_assert("Should return -1, removing after heap address", res == -1);
    
   
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
}*/
 
 static char * all_tests() {
     mu_run_test(test_findHeapIndexBySize);
     mu_run_test(test_findAndSetVariableIndex);
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
