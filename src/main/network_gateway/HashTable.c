#include <stdlib.h>
#include <stdio.h>
#include "Key.h"
#include "KeyHandler.h"
#include "LinkedListNode.h"
#include "LinkedListHandler.h"
#include "MemoryManagerSubheap.h"
#include "Configuration.h"

LinkedListNode** hashTable;
int hashTableSize;

int getIndexByHashKey(Key* key) { return hashCode(key) % hashTableSize; }

LinkedListNode* getLinkedListNode(Key* key) {
    int hashTableIndex =  getIndexByHashKey(key);

    LinkedListNode* root = hashTable[hashTableIndex];

    return findLinkedListNodeByKey(root, key);
}


char insertHashTable(Key* key) {
    Key* copyKey = (Key*) allocate(sizeof(Key));
    LinkedListNode* newNode = (LinkedListNode*) allocate(sizeof(LinkedListNode));

    if (NULL == copyKey || NULL == newNode)
    { return INSERT_FAIL; }

    copyKey->port	= key->port;
    copyKey->ip 	= key->ip;
    newNode->key 	= copyKey;

    int hashTableIndex = hashCode(copyKey) % hashTableSize;

    LinkedListNode* oldRoot = hashTable[hashTableIndex];

    hashTable[hashTableIndex] = newNode;
    newNode->next = oldRoot;


    return INSERT_SUCCESS;
}

char findHashTable(Key* key) {
    if (NULL == key) { return FIND_FAIL; }

    LinkedListNode* result = getLinkedListNode(key);

    return NULL == result ? FIND_FAIL : FIND_SUCCESS;
}

char alterHashTable(Key* source, Key* target) {
    if (NULL == source)
    { return ALTER_FAIL; }

    LinkedListNode* sourceNode = getLinkedListNode(source);

    if (NULL == sourceNode)
    { return ALTER_FAIL; }

    int hashTableIndex = hashCode(source) % hashTableSize;

    LinkedListNode* root = hashTable[hashTableIndex];

    char removeStatus = removeLinkedListNode(root, sourceNode);

    switch (removeStatus)  {
    case LINKED_LIST_NODE_ROOT_IS_CANT_BE_REMOVED:
	hashTable[hashTableIndex] = root->next;
	break;
    case LINKED_LIST_NODE_NOT_FOUND:
	printf("%s", "Key and node not found!\n");
	return ALTER_FAIL;
	break;
    default:
	break;
    }

    if (NULL == target) {
	//removeVar((char*) sourceNode->key);
	//removeVar((char*) sourceNode);
	return REMOVE_SUCCESS;
    }

    sourceNode->key				= target;
    hashTableIndex				= hashCode(target) % hashTableSize;
    root						= hashTable[hashTableIndex];
    hashTable[hashTableIndex]	= sourceNode;
    sourceNode->next 			= root;

    return ALTER_SUCCESS;
}

char initHashTable(int size) {
    int variablesSize[3] = {sizeof(Key), sizeof(LinkedListNode), size * sizeof(LinkedListNode*)};
    int variablesCount[3] = {size, size, 1};
    char subheapCount = 3;

    if (INITIAL_SUCCESS != init(variablesSize, variablesCount, subheapCount)) {
	printf("%s", "Memory manager can't init\n");
	exit(-1);
    }

    hashTableSize = size;
    hashTable = (LinkedListNode**) allocate(size * sizeof(LinkedListNode*));


    return (NULL == hashTable) ? HASH_TABLE_INIT_FAIL : HASH_TABLE_INIT_SUCCESS;
}
