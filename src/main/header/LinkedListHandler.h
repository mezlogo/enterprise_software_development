#ifndef LINKED_LIST_HANDLER_H
#define LINKED_LIST_HANDLER_H

#include "Key.h"
#include "LinkedListNode.h"

char addLinkedListNode(LinkedListNode* root, LinkedListNode* next);
char removeLinkedListNode(LinkedListNode* root, LinkedListNode* next);
LinkedListNode* findLinkedListNodeByKey(LinkedListNode* root, Key* key);
#endif
