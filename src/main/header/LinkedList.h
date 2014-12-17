#ifndef LINKED_LIST_H
#define LINKED_LIST_H

#include "Key.h"

typedef struct LinkedList LinkedList;

struct LinkedList {
    Key key;
    LinkedList* next;
} __attribute__((packed));

#endif
