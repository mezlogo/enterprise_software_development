#include "Configuration.h"

#define validation(variable) if (MAX_VARIABLES_COUNT <= ++variable) variable = 0;

long putIndex = 0;
long getIndex = 0;

char* list[MAX_VARIABLES_COUNT];

void put(char* variable) {
    validation(putIndex);

    list[putIndex] = variable;
}

char* next() {
    validation(getIndex);

    return list[getIndex];
}
