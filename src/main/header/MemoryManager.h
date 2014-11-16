#include <stdio.h>
#include <stdlib.h>

char* allocate(int size);

int removeVar(void* var);

int initHeap(char _heapsCount, int* _heapsVariableSize, int* _heapsVariablesCount);
