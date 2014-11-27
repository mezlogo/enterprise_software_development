#include <stdio.h>
#include "ArrayHandler.h"
#include "ErrorCode.h"
#include "Subheap.h"
#include "SubheapHandler.h"

#define MAX_HEAP_SIZE 10000
#define MAX_HEAPS_COUNT 10
#define MAX_VARIABLES_COUNT 1000

char heap[MAX_HEAP_SIZE];
char variales[MAX_VARIABLES_COUNT];
char currentSubheapCount;
struct Subheap subheaps[MAX_HEAPS_COUNT];

int maxVariablesSize = 10;

/*Выделение памяти
 * Входной параметр: размер переменной
 * Выходной: Указатель на область в куче, способный хранить нужный размер, либо 0
 * Проверка входного параметра: больше нуля и не больше максимального размера переменных последней подкучи
 * Алгоритм:
 * 1) Найти индекс первой подходящей подкучи
 * 2) Найти первую свобдную переменную подкучь, начиная с индексом
 * 3) Занять переменную, по найденому индексу
 * 4) Возвратить (размер переменных найденой подкучи) * (индекс свободной переменной) + указатель на кучу найденой подкучи
 * */
char* allocate(int size){
	if (size <= 0 || maxVariablesSize < size) {
		printf("No subheaps found, that can contain varables size: %d\n", size);
		return NULL;
	}
	
	char index = findHeapIndexBySize(subheaps, currentSubheapCount, size);
	int allocateVariableIndex = -1;
	struct Subheap subheap;
	
	for(; index <= currentSubheapCount; index++){
		subheap = subheaps[index];
		allocateVariableIndex = findFirstZero(subheap.variables, subheap.variablesCount);
		if (0 <= allocateVariableIndex){
			subheap.variables[allocateVariableIndex] = 1;
			break;
		}
	}
	
	if (allocateVariableIndex == -1) {
		printf("No free variables, that can contain varables size: %d\n", size);
		return NULL;
	}
		
	return subheap.heap + subheap.variablesSize * allocateVariableIndex;
}

int removeVar(void* var){
	return 0;
}

/*Инициализация
 * Входной параметр: размеры переменных подкучь, количество переменных в подкучах, количество подкуч
 * Выходной: код ошибки/успеха
 * Проверка входного параметра: 
 * 	-	количество подкуч больше нуля и не больше максимального количества подкучь
 * 	-	сумма перемножение элементов двух массивов = размер переменной * количество не больше размера всей кучи
 * 	-	массив размеров по возрастающей
 * 	-	массив размеров и количества состоит из элементов больше нуля
 * Алгоритм:
 * 1) Обнулить необходимые переменные
 * 2) Инициализировать подкучи
 * 3) Вычислить кэшируеммые данные:
 * 	-	Указатель на последний байт последней кучи
 * 	-	Максимальный размер хранимых переменных
 * */
int init(int* variablesSize, int* variablesCount, char subheapCount){
	if(subheapCount <= 0 || 
		MAX_HEAPS_COUNT < subheapCount || 
		ONLY_ACSENDING != isAscending(variablesSize, subheapCount) ||
		ONLY_POSITIVES != isOnlyPositive(variablesSize, subheapCount) ||
		ONLY_POSITIVES != isOnlyPositive(variablesCount, subheapCount)) 
			return INITIAL_INPUT_PARAMS_ERROR;
	
	long sumOfMul = sumOfMulOfTwoArray(variablesSize, variablesCount, subheapCount);
	int sumOfArrayVarriables = sumOfArray(variablesCount, subheapCount);

	if(MAX_HEAP_SIZE < sumOfMul ||
		MAX_VARIABLES_COUNT < sumOfArrayVarriables) 
		return INITIAL_ERROR_MANAGER_TOO_SMALL;
			
	currentSubheapCount = subheapCount;		
	
	char index = 0;
	int variablesOffset = 0;
	long heapOffset = 0;
	for(; index < currentSubheapCount; index++){
		struct Subheap currentSubheap = subheaps[index];
		currentSubheap.variables = variales + variablesOffset;
		currentSubheap.variablesCount = variablesCount[index];
		currentSubheap.variablesSize = variablesSize[index];
		currentSubheap.heap = heap + heapOffset;
		
		variablesOffset += currentSubheap.variablesCount;
		heapOffset += currentSubheap.variablesCount * currentSubheap.variablesSize;
	}
	
	resetAllChars(variales, sumOfArrayVarriables);

	return 0;
}

struct Subheap * getSubheaps(){
	return subheaps;
}

char getSubheapCount() {
	return currentSubheapCount;
}

char* getHeap(){
	return heap;
}
