#include <stdlib.h>
#include <stdio.h>

#include "Timer.h"
#include "CyclicList.h"
#include "Logger.h"
#include "Random.h"
#include "SizeGenerator.h"
#include "TaskRunner.h"

#include "MemoryManagerSubheap.h"

#include "Configuration.h"

int (*generate)();

int parent() {
    int size = generate();

    unsigned long startTime = getULongNano();
    char* allocateVariable = allocate(size);
    unsigned long time = calcOffsetULong(startTime);

    int result = CRASH;

    if (NULL != allocateVariable) {
	logPrimary(time);
	put(allocateVariable);
	result = NO_CRASH;
    }

    return result;
}

void child() {
    if (generateIntByWidth(REMOVE_MAX_CHANCE) < REMOVE_CHANCE) {
	char* toRemove = next();
	int result = 0;

	unsigned long startTime = getULongNano();
	result = removeVar(toRemove);
	unsigned long time = calcOffsetULong(startTime);

	if (VARIABLE_REMOVE_SUCCESS == result) 	{ logSecondary(time); }
	else 									{ printf("%s", "Remove issue occurs\n"); }
    }
}

void preIteration() {
    reset();
}

void postIteration() {
    show();
}

void startAnalyze(int (*generateMethod)(), char* msg) {
    printf("%s", msg);

    int variablesSize[] = ANALYZE_VARIABLES_SIZE;
    int variablesCount[] = ANALYZE_VARIABLES_COUNT;
    char subheapCount = ANALYZE_SUBHEAPS_COUNT;

    int memoryManagerInitResult = init(variablesSize, variablesCount, subheapCount);

    if (INITIAL_SUCCESS != memoryManagerInitResult) {
	printf("%s%d\n", "\nIncorrect initial code: ", memoryManagerInitResult);
	return;
    }
    generate = generateMethod;
    tasksRun(&parent, &child, &preIteration, &postIteration, SESSION_COUNT, ITERATION_COUNT);
}

void start() {
    startAnalyze(&getFix, "<<<<<<<<<<<<<<<<<<<<<<FIX>>>>>>>>>>>>>>>>>\n");
    startAnalyze(&getRange, "<<<<<<<<<<<<<<<<<<<<<<RANGE>>>>>>>>>>>>>>>>>\n");
}

