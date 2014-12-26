#include "Subheap.h"

char findHeapIndexBySize(Subheap*   subheaps,
						 char subheapCount, int size) {
	int index = 0;

	for (; index < subheapCount; index++)
		if (size <= subheaps[index].variablesSize)
		{ break; }

	return index;
}

char findHeapIndexByPointer(Subheap* subheaps,
							char subheapCount, char* variable) {
	int index = subheapCount - 1;

	for (; 0 <= index; index--)
		if (subheaps[index].heap <= variable)
		{ break; }

	return index;
}

long initSubheaps(Subheap* subheaps,
				  char subheapCount, char* variables, char* heap,
				  int* variablesSize, int* variablesCount) {
	//Заполняем для каждой подкучи необходимые данные
	int index = 0;
	int variablesOffset = 0;
	long heapOffset = 0;

	for (; index < subheapCount; index++) {
		Subheap* currentSubheap = &subheaps[index];
		//Смещение переменных
		currentSubheap->variables = variables +
									variablesOffset;
		//Количество переменных
		currentSubheap->variablesCount =
			variablesCount[index];
		//Размер переменных
		currentSubheap->variablesSize =
			variablesSize[index];
		//Смещение относительно начала кучи
		currentSubheap->heap = heap + heapOffset;

		variablesOffset += currentSubheap->variablesCount;
		heapOffset += currentSubheap->variablesCount *
					  currentSubheap->variablesSize;
	}

	return heapOffset;
}
