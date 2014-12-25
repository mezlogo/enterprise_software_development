#include <stdlib.h>
#include <stdio.h>

#include "Key.h"
#include "KeyHandler.h"
#include "MemoryManagerSubheap.h"
#include "AVLNodeHandler.h"
#include "Configuration.h"

AVLNode* root;

char insertAVLTree(Key* key) {
    if (NULL == key)
    { return INSERT_FAIL; }

    Key* copyKey = (Key*) allocate(sizeof(Key));
    AVLNode* newNode = (AVLNode*) allocate(sizeof(AVLNode));

    if (NULL == copyKey || NULL == newNode)
    { return INSERT_FAIL; }

    copyKey->port	= key->port;
    copyKey->ip 	= key->ip;
    newNode->key 	= copyKey;

    root = insertAVLByNode(root, newNode);

    return INSERT_SUCCESS;
}

char findAVLTree(Key* key) {
    if (NULL == key) { return FIND_FAIL; }

    AVLNode* result = findAVLNode(root, key);

    return NULL == result ? FIND_FAIL : FIND_SUCCESS;
}

char alterAVLTree(Key* source, Key* target) {
    if (NULL == source)
    { return ALTER_FAIL; }

    void deleteOp(AVLNode * toDelete) {
	removeVar((char*) toDelete->key);
	removeVar((char*) toDelete);
    }

    root = removeAVLNode(root, source, &deleteOp);

    if (NULL == target) {
	return REMOVE_SUCCESS;
    }

    char insertResult = insertAVLTree(target);
    return INSERT_SUCCESS == insertResult ? ALTER_SUCCESS : ALTER_FAIL;
}

char initAVLTree(int size) {
    root = NULL;
    int variablesSize[2] = {sizeof(Key), sizeof(AVLNode)};
    int variablesCount[2] = {size, size};
    char subheapCount = 2;

    return (INITIAL_SUCCESS == init(variablesSize, variablesCount, subheapCount)) ? HASH_TABLE_INIT_SUCCESS : HASH_TABLE_INIT_FAIL;
}
