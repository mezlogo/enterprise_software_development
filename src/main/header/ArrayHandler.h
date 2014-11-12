int findHeapIndexBySize(long* heapsSize, int heapsCount, int allocateSize);

int findHeapIndexByPointer(char** heapsAddress, int heapsCount, char* pointer);

int findAndSetVariableIndex(char* varibles, int varibleCount);

int isAscendingOrder(int* heapsSize, int heapCount);

long sumOfHeapByVarCountAndSize(int* heapsSize, int* heapsVariables, int heapsCount);

int initHeapsAddress(char** heapsAddress, char* heap, int* heapsSize, int* heapsVariables, int heapsCount);

int initHeapsVariables(char** heapsAddressVariables, char* variables, int* heapsVariables, int heapsCount);
