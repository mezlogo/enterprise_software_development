#include "Subheap.h"

char* allocate(int size);

int removeVar(void* var);

int init(int* variablesSize, int* variablesCount, int subheapCount);

char* getHeap();

struct Subheap * getSubheaps();
