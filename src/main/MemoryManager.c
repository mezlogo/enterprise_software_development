#include <stdio.h>
#include <stdlib.h>
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

int heapsSize[HEAP_SIZE];
int heapsAddress[HEAP_SIZE];
int countVarribleInsidHeap[HEAP_SIZE];
int offsetVarribles[HEAP_SIZE];

/*
"Выделение памяти"
1) Находим индекс под-кучи в которой может храниться данная переменная.
2) Получаем индекс-смещение для данной под-кучи, среди всех переменных кучи (иначе инкремент кучи, и т.д) 
.., если он существует, то "забиваем" его.

*/
void* allocate(int size){
    return getPointer(heap, HEAPS_COUNT, heapsSize, heapsAddress, offsetVarribles, countVarribleInsidHeap, varribles, size);
}

int main(int argc, char** argv) {

    return (EXIT_SUCCESS);
}

