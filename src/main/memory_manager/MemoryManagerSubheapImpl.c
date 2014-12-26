#include <stdio.h>
#include "ArrayHandler.h"
#include "Configuration.h"
#include "Subheap.h"
#include "SubheapHandler.h"

//Состояние управляющего памяти
char heap[MAX_HEAP_SIZE] = {0};
char variables[MAX_VARIABLES_COUNT];
Subheap subheaps[MAX_HEAPS_COUNT];

//Динамическая инициализация
char currentSubheapCount;

//Кэшируем данные
int maxVariablesSize = 0;
char* lastByte;

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
char* allocate(int size) {
	if (size <= 0 || maxVariablesSize < size) {
//		printf("No subheaps found, that can contain varables size: %d\n", size);
		return NULL;
	}

	int subheapIndex = findHeapIndexBySize(subheaps,
										   currentSubheapCount, size);
	int allocateVariableIndex = -1;
	Subheap* currentSubheap;

	for (; subheapIndex <= currentSubheapCount;
			subheapIndex++) {
		currentSubheap = &subheaps[subheapIndex];
		allocateVariableIndex = findFirstZero(
									currentSubheap->variables,
									currentSubheap->variablesCount);

		if (0 <= allocateVariableIndex) {
			currentSubheap->variables[allocateVariableIndex] =
				1;
			break;
		}
	}

	if (allocateVariableIndex == -1) {
//		printf("No free variables, that can contain varables size: %d\n", size);
		return NULL;
	}

	char* result = currentSubheap->heap +
				   currentSubheap->variablesSize *
				   allocateVariableIndex;

	resetAllChars(result, size);

	return result;
}

/*Освобождение памяти
 * Входной параметр: указатель переменной
 * Выходной: Код результата
 * Проверка входного параметра: Не меньше начала кучи, и не больше последнего байта кучи
 * Алгоритм:
 * 1) Найти индекс подходящей подкучи
 * 2) Вычислить индекс внутри переменных подкучи как (перем - куча подкучи) / размер переменных подкучи
 * 3) Освободить переменную с вычисленным индексом
 * */
int removeVar(char* variable) {
	if (variable < heap || lastByte < variable) { return VARIABLE_REMOVE_FAIL; }

	int subheapIndex = findHeapIndexByPointer(
						   subheaps, currentSubheapCount, variable);

	Subheap* targetSubheap = &subheaps[subheapIndex];

	targetSubheap->variables[((int)(variable -
									targetSubheap->heap)) /
							 targetSubheap->variablesSize] = 0;

	return VARIABLE_REMOVE_SUCCESS;
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
int init(int* variablesSize, int* variablesCount,
		 char subheapCount) {
	//Валидация: количества подкучь, положительные значения в массивах и размеры по возростанию
	if (subheapCount <= 0 ||
			MAX_HEAPS_COUNT < subheapCount ||
			ONLY_ACSENDING != isAscending(variablesSize,
										  subheapCount) ||
			ONLY_POSITIVES != isOnlyPositive(variablesSize,
					subheapCount) ||
			ONLY_POSITIVES != isOnlyPositive(variablesCount,
					subheapCount))
	{ return INITIAL_INPUT_PARAMS_ERROR; }

	//Вычисляем сколько требуется байт в куче и сколько переменных можем хранить
	long sumOfMul = sumOfMulOfTwoArray(variablesSize,
									   variablesCount, subheapCount);
	int sumOfArrayVarriables = sumOfArray(
								   variablesCount, subheapCount);

	//Валидация: поместится ли в выделенную кучю и переменные
	if (MAX_HEAP_SIZE < sumOfMul ||
			MAX_VARIABLES_COUNT < sumOfArrayVarriables)
	{ return INITIAL_ERROR_MANAGER_TOO_SMALL; }

	//Валидация пройдена успешна, запоминаем количество подкуч
	currentSubheapCount = subheapCount;

	//Заполняем для каждой подкучи необходимые данные
	long heapOffset = initSubheaps(subheaps,
								   subheapCount, variables, heap, variablesSize,
								   variablesCount);

	//Сбрасываем занятые переменные
	resetAllChars(variables, sumOfArrayVarriables);

	//Кэшируем максимальный размер и адрес последнего байта
	maxVariablesSize = subheaps[currentSubheapCount -
								1].variablesSize;
	lastByte = heap + heapOffset - 1;

	return INITIAL_SUCCESS;
}

Subheap* getSubheaps() {
	return subheaps;
}

char getSubheapCount() {
	return currentSubheapCount;
}

char* getLastByte() {
	return lastByte;
}

char* getHeap() {
	return heap;
}

char* getVariables() {
	return variables;
}
