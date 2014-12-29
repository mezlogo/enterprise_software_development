#include <stdlib.h>
#include <stdio.h>

#include "Key.h"
#include "AVLNode.h"
#include "KeyHandler.h"
#include "MemoryManagerSubheap.h"
#include "AVLNodeHandler.h"
#include "Configuration.h"

AVLNode* root;

char insertAVLTree(Key* key) {
	if (NULL == key)
	{ return INSERT_FAIL; }

	Key* copyKey = (Key*) allocate(sizeof(Key));
	AVLNode* newNode = (AVLNode*) allocate(sizeof(
			AVLNode));

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
	if (NULL == source || NULL == root)
	{ return ALTER_FAIL; }

	AVLNode* srcNode;
	void deleteOp(AVLNode * toDelete) {
		srcNode = toDelete;
	}

	root = removeAVLNode(root, source, &deleteOp);

	if (NULL == target) {
		removeVar((char*) srcNode->key);
		removeVar((char*) srcNode);
		return REMOVE_SUCCESS;
	}

	srcNode->key->ip = target->ip;
	srcNode->key->port = target->port;
	srcNode->left = NULL;
	srcNode->right = NULL;

	root = insertAVLByNode(root, srcNode);

	return ALTER_SUCCESS;
}

char initAVLTree(int size) {
	root = NULL;
	int variablesSize[2] = {sizeof(Key), sizeof(AVLNode)};
	int variablesCount[2] = {size, size};
	char subheapCount = 2;

	char result = init(variablesSize, variablesCount, subheapCount);

	return (INITIAL_SUCCESS == result) ? HASH_TABLE_INIT_SUCCESS :
		   HASH_TABLE_INIT_FAIL;
}
