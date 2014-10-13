#include <stdio.h>
#include <stdlib.h>



//1) Находим индекс под-кучи в которой может храниться данная переменная.
int getHeapIndex(long* heapsSize, int heapsCount, int needSize){
    int index = 0;
    for(; index < heapsCount; index++)
        if (needSize <= heapsSize[index])
            return index;
    return -1;
}

//2) Получаем индекс-смещение для данной под-кучи, среди всех переменных кучи
//.., если он существует, то "забиваем" его.
int findSetFreeVarribleIndex(char* varribles, int currentVarribleSize){
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
void* getPointer(long heap, int heapsCount, long* heapsSize, long* heapsAddress, int* offsetVarribles, int* countVarribleInsidHeap, char* varribles, long size){
    int heapIndex = getHeapIndex(heapsSize, heapsCount, size);
    if(heapIndex < 0){
        printf("There is no heap, which can store those size");
        return NULL;
    }
    int offsetVarible = -1;
    for(;heapIndex < heapsCount; heapIndex++){
        int varribleOffsetInsideCurrentHeap = offsetVarribles[heapIndex];
        offsetVarible = findSetFreeVarribleIndex(&varribles[varribleOffsetInsideCurrentHeap], countVarribleInsidHeap[varribleOffsetInsideCurrentHeap]);
        if (0 <= offsetVarible) break;
    }

    long result = heapsAddress[heapIndex] + offsetVarible * heapsSize[heapIndex];
    return ((void*) result);
}
