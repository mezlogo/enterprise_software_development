#include <stdlib.h>
#include "Key.h"
#include "KeyHandler.h"
#include "Configuration.h"
#include "LinkedListNode.h"


char addLinkedListNode(LinkedListNode* root,
					   LinkedListNode* next) {
	if (NULL == root)
	{ return LINKED_LIST_NODE_ROOT_IS_NULL; }

	LinkedListNode* currentNode = root;

	while (NULL != currentNode->next)
	{ currentNode = currentNode->next; }

	currentNode->next = next;

	return LINKED_LIST_NODE_SUCCESS_OP;
}

char removeLinkedListNode(LinkedListNode* root,
						  LinkedListNode* target) {
	if (target == root)
	{ return LINKED_LIST_CANT_REMOVE_ROOT; }


	LinkedListNode* currentNode = root;

	while (NULL != currentNode) {
		if (target == currentNode->next) {
			currentNode->next = target->next;
			return LINKED_LIST_NODE_SUCCESS_OP;
		}

		currentNode = currentNode->next;
	}

	return LINKED_LIST_NODE_NOT_FOUND;
}

LinkedListNode* findLinkedListNodeByKey(LinkedListNode* root, Key* key) {
	if (NULL == key) { return NULL; }

	LinkedListNode* current = root;

	while (NULL != current) {
		if (0 == compareKeys(key, current->key))
		{ return current; }

		current = current->next;
	}

	return NULL;
}
