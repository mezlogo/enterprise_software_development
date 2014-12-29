#include <stdlib.h>
#include <stdio.h>

#include "Key.h"
#include "BNode.h"
#include "KeyHandler.h"
#include "MemoryManagerSubheap.h"
#include "BNodeHandler.h"
#include "Configuration.h"


BNode* root;

char insertBTree(Key* key) {
	if (NULL == key)
	{ return INSERT_FAIL; }

	Key* copyKey = (Key*) allocate(sizeof(Key));
	BNode* newNode = (BNode*) allocate(sizeof(BNode));

	if (NULL == copyKey || NULL == newNode)
	{ return INSERT_FAIL; }

	copyKey->port	= key->port;
	copyKey->ip 	= key->ip;
	newNode->key 	= copyKey;

	if (NULL == root) {
		root = newNode;

	} else {
		char result = insertBNodeInsideRoot(root, newNode);

		if (TREE_INSERT_OK != result) {
			printf("%s", "B tree insert error\n");
			removeVar((char*) copyKey);
			removeVar((char*) newNode);
			return INSERT_FAIL;
		}
	}

	return INSERT_SUCCESS;
}

char findBTree(Key* key) {
	if (NULL == key) { return FIND_FAIL; }

	BNode* result = findBNodeInsideRoot(root, key);

	return NULL == result ? FIND_FAIL : FIND_SUCCESS;
}

char alterBTree(Key* source, Key* target) {
	if (NULL == source || NULL == root)
	{ return ALTER_FAIL; }

	BNode* srcNode;
	void deleteOp(BNode * toDelete) {
		srcNode = toDelete;
	}
	char removeStatus;
	root = deleteBNodeFromRoot(root, source, &deleteOp, &removeStatus);

	if (NULL == target) {
		removeVar((char*) srcNode->key);
		removeVar((char*) srcNode);
		return REMOVE_SUCCESS;
	}

	srcNode->key->ip = target->ip;
	srcNode->key->port = target->port;
	srcNode->left = NULL;
	srcNode->right = NULL;

	char insertResult = insertBNodeInsideRoot(root, srcNode);
	return TREE_INSERT_OK == insertResult ? ALTER_SUCCESS : ALTER_FAIL;
}


char initBTree(int size) {
	root = NULL;
	int variablesSize[2] = {sizeof(Key), sizeof(BNode)};
	int variablesCount[2] = {size, size};
	char subheapCount = 2;

	char result = init(variablesSize, variablesCount, subheapCount);

	return (INITIAL_SUCCESS == result) ? HASH_TABLE_INIT_SUCCESS :
		   HASH_TABLE_INIT_FAIL;
}
