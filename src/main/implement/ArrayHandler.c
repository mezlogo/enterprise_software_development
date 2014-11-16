#include <stdio.h>
#include <stdlib.h>

int findHeapIndexBySize(long* heapsSize, int heapsCount, int allocateSize){
    int index = 0;
    for(; index < heapsCount; index++)
        if (allocateSize <= heapsSize[index])
            break;
    return index;
}

int findAndSetVariableIndex(char* varibles, int varibleCount){
    int index = 0;
    for(; index < varibleCount; index++)
        if (varibles[index] == 0)
            break;
    
    if (index == varibleCount) return -1;
    
    varibles[index] = 1;
    return index;    
}

int isAscendingOrder(int* heapsSize, int heapCount){
    int prev = 0;
    int index = 0;
    for(; index < heapCount; index++)
        if (prev < heapsSize[index]) prev = heapsSize[index];
        else return index;
    return -1;
}

int findHeapIndexByPointer(char** heapsAddress, int heapsCount, char* pointer){
    int index = heapsCount - 1;
    for(; 0 <= index; index--)
        if(heapsAddress[index] <= pointer)
            break;
    
    return index;
}

long sumOfHeapByVarCountAndSize(int* heapsSize, int* heapsVariables, int heapsCount){
    long result = 0;
    int index = 0;
    for(; index < heapsCount; index++)
        if (heapsSize[index] <= 0 || heapsVariables[index] <= 0) {result = -1; break;}
        else result = result + heapsSize[index] * heapsVariables[index];
    
    return result;
}


int initHeapsAddress(char** heapsAddress, char* heap, int* heapsSize, int* heapsVariables, int heapsCount){
    heapsAddress[0] = heap;
    int index = 1;
    long offset = 0;
    for(; index < heapsCount; index++){
        offset = offset + heapsSize[index - 1] * heapsVariables[index - 1];
        heapsAddress[index] = heap + offset;
    }
    return 1;        
}

int initHeapsVariables(char** heapsAddressVariables, char* variables, int* heapsVariables, int heapsCount){
    heapsAddressVariables[0] = variables;
    int index = 1;
    long offset = 0;
    for(; index < heapsCount; index++){
        offset = offset + heapsVariables[index - 1];
        heapsAddressVariables[index] = variables + offset;
    }
    return 1;
}

int resetAllChars(char* heapsVariables, int variablesCount){
    int index = 0;
    for(; index < variablesCount; index++){
        heapsVariables[index] = 0;
    }
    return 1;
}