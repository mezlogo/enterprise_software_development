#include <stdio.h>
#include <stdlib.h>
#include "ArrayHandler.h"

/*Представляем основной модуль реализующий управление памяти*/


////////
//Поля//
////////
//Количество подкуч. Каждая подкуча содержит переменные определенного размера
#define HEAPS_COUNT 5
//Собственно количество байт для хранения
#define HEAP_SIZE 100000

//Память-куча для хранения данных
char heap[HEAP_SIZE];
//Переменные
char varribles[100] = {0};

long heapsSize[HEAPS_COUNT];
long heapsAddress[HEAPS_COUNT];
int countVarribleInsidHeap[HEAPS_COUNT];
int offsetVarribles[HEAPS_COUNT];

/*
"Выделение памяти"
1) Находим индекс под-кучи в которой может храниться данная переменная.
2) Получаем индекс-смещение дял массива переменных данной под-кучи, среди всех переменных кучи (иначе инкремент кучи, и т.д) 
.., если он существует, то "забиваем" его.
3) 
*/
char* allocate(int size){
    return getPointer(heap, HEAPS_COUNT, heapsSize, heapsAddress, offsetVarribles, countVarribleInsidHeap, varribles, size);
}

int removeVar(void* var){
    return removePointer(var, HEAPS_COUNT, heapsSize, (void**) heapsAddress, offsetVarribles, varribles, HEAP_SIZE);
}

int main(int argc, char **argv) {return 0;}