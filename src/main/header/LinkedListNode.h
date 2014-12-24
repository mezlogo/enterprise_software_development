#ifndef LINKED_LIST_NODE_H
#define LINKED_LIST_NODE_H

#include "Key.h"

typedef struct LinkedListNode LinkedListNode;

struct LinkedListNode {
    Key* key;
    LinkedListNode* next;
} __attribute__((packed));

#endif
