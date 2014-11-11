#include <stdio.h>
#include <stdlib.h>


int findHeapIndexBySize(long* heapsSize, int heapsCount, int allocateSize){
    int index = 0;
    for(; index < heapsCount; index++)
        if (allocateSize <= heapsSize[index])
            break;
    return index;
}

//1) Находим индекс под-кучи в которой может храниться данная переменная.
int getHeapIndex(long* heapsSize, int heapsCount, int needSize){
    int index = 0;
    for(; index < heapsCount; index++)
        if (needSize <= heapsSize[index])
            return index;
    return -1;
}

//2) Получаем индекс-смещение для данной под-кучи, среди всех переменных кучи
//.., если он существует, то "забиваем" его еденичкой.
int findAndSetFreeVarribleIndex(char* varribles, int currentVarribleSize){
    int index = 0;
    for(; index < currentVarribleSize; index++)
        if (0 == varribles[index]){ varribles[index] = 1; return index; }
        
    return -1;
}

int sumOfArray(int* array, int size){
    int result = 0;
    int index = 0;
    for(; index < size; index++)
        result += array[index];
    
    return result;
}

//Реализация нахождаения места в кучи, и возвращение указателя на нее
char* getPointer(char* heap, int heapsCount, long* heapsSize, void** heapsAddress, int* offsetVarribles, int* countVarribleInsidHeap, char* varribles, long size){
    int heapIndex = getHeapIndex(heapsSize, heapsCount, size);
    if(heapIndex < 0) return NULL;
    
    int offsetVarible = -1;
    for(;heapIndex < heapsCount; heapIndex++){
        int varribleOffsetInsideCurrentHeap = offsetVarribles[heapIndex];
        offsetVarible = findAndSetFreeVarribleIndex(&varribles[varribleOffsetInsideCurrentHeap], countVarribleInsidHeap[heapIndex]);
        if (0 <= offsetVarible) break;
    }
    
    char* result = heapsAddress[heapIndex] + offsetVarible * heapsSize[heapIndex];
    return result;
}

//Реадизация удаления
int removePointer(void* pointerToRemove, int heapsCount, long* heapsSize, void** heapsAddress, int* offsetVarribles, char* varribles, long heapSize){
    if ((pointerToRemove < heapsAddress[0]) || (heapSize + heapsAddress[0] < pointerToRemove)) return -1;
    
    int heapIndex = 0;
    
    for(;heapIndex < heapsCount; heapIndex++)
        if(pointerToRemove < heapsAddress[heapIndex + 1])
            break;
    long offsetVarribleInsideHeap = (pointerToRemove - heapsAddress[heapIndex])/heapsSize[heapIndex];
    
    
    varribles[offsetVarribles[heapIndex] + offsetVarribleInsideHeap] = 0;
    
    return 0;
}