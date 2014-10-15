int getHeapIndex(long* heapsSize, int heapsCount, int needSize);

int findAndSetFreeVarribleIndex(char* varribles, int currentVarribleSize);

int sumOfArray(int* array, int size);

char* getPointer(char* heap, int heapsCount, long* heapsSize, long* heapsAddress, int* offsetVarribles, int* countVarribleInsidHeap, char* varribles, long size);

int removePointer(void* pointerToRemove, int heapsCount, long* heapsSize, void** heapsAddress, int* offsetVarribles, char* varribles, long heapSize);