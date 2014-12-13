#ifndef SUBHEAP_H
#define SUBHEAP_H

typedef struct Subheap {
    char* variables;
    int variablesCount;
    int variablesSize;
    char* heap;
} Subheap;

#endif /*SUBHEAP_H*/
