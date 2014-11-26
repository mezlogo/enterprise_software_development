#include "Subheap.h"

char findHeapIndexBySize(struct Subheap  * subheaps, char subheapCount, int size){
	char index = 0;
	
	for(; index < subheapCount; index++)
		if(size <= subheaps[index].variablesSize)
			break;
			
	return index;
}

char findHeapIndexByPointer(struct Subheap * subheaps, char subheapCount, char * variable){
	char index = subheapCount - 1;
	
	for(; 0 <= index; index--)
		if(subheaps[index].heap <= variable)
			break;
			
	return index;
}
