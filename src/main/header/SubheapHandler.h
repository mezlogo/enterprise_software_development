#include "Subheap.h"

char findHeapIndexBySize(Subheap * subheaps, char subheapCount, int size);

char findHeapIndexByPointer(Subheap * subheaps, char subheapCount, char * variable);

long initSubheaps(Subheap * subheaps, char subheapCount, char * variable, char * heap, int* variablesSize, int* variablesCount);
