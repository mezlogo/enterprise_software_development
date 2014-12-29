#include <stdlib.h>
#include <stdio.h>

#include "Configuration.h"
#include "Key.h"
#include "KeyHandler.h"
#include "BNode.h"

BNode* findBNodeInsideRoot(BNode* root, Key* key) {
	if (NULL == key) { return NULL; }

	BNode* currentNode = root;

	while (NULL != currentNode) {
		switch (compareKeys(currentNode->key, key)) {
		case 1:
			currentNode = currentNode->left;
			break;

		case -1:
			currentNode = currentNode->right;
			break;

		case 0:
			return currentNode;
			break;
		}
	}

	return NULL;
}

char insertBNodeInsideRoot(BNode* root, BNode* target) {
	BNode* currentNode = root;

	while (NULL != currentNode) {
		switch (compareKeys(currentNode->key, target->key)) {
		case 1:
			if (NULL == currentNode->left) {
				currentNode->left = target;
				return TREE_INSERT_OK;
			}

			currentNode = currentNode->left;
			break;

		case -1:
			if (NULL == currentNode->right) {
				currentNode->right = target;
				return TREE_INSERT_OK;
			}

			currentNode = currentNode->right;
			break;

		case 0:
			return TREE_INSERT_NOT_UNIQ;
			break;
		}
	}

	return -5;
}

BNode** getBNodeParentAnFindTarget(BNode* root, Key* key) {
	BNode** currentParentPointer = NULL;
	BNode* currentChild = NULL;

	//Return if root == target
	switch (compareKeys(root->key, key)) {
	case    1:
		currentParentPointer = &root->left;
		break;

	case   -1:
		currentParentPointer = &root->right;
		break;

	case    0:
		return NULL;
		break;

	default  :
		printf("%s", "Compare error #10\n");
	}

	currentChild = *currentParentPointer;

	while (NULL != (currentChild = *currentParentPointer)) {
		switch (compareKeys(currentChild->key, key)) {
		case 1:
			currentParentPointer = &currentChild->left;
			break;

		case -1:
			currentParentPointer = &currentChild->right;
			break;

		case 0:
			return currentParentPointer;
			break;

		default:
			printf("%s", "Compare error #11\n");
		}

	}

	return NULL;
}

BNode** getBNodeParentOfLefter(BNode* root) {
	BNode** currentParentPointer = NULL;
	BNode* currentChild = NULL;

	if ((NULL == root)
			|| (NULL == (currentParentPointer = &root->left))
			|| (NULL == (currentChild = *currentParentPointer))) { return NULL; }


	while (NULL != currentChild->left) {
		currentParentPointer = &currentChild->left;
		currentChild = *currentParentPointer;
	}

	return currentParentPointer;
}

BNode* deleteBNodeFromRoot(BNode* root, Key* key,  void (*deleteOp)(BNode*), char* status) {
	if (NULL == root || NULL == key) { return root; }

	BNode* target = root;
	BNode**   parentPointerTarget;

	if (0 == compareKeys(target->key, key)) {
		if ((NULL == target->left) && (NULL == target->right)) {
			root = NULL;

		} else if (NULL == target->left) {
			root = target->right;

		} else if (NULL == target->right) {
			root = target->left;

		} else {
			BNode*	successor = NULL;
			BNode** successorParentPointer = getBNodeParentOfLefter(target->right);

			if (NULL == successorParentPointer) {
				successor = target->right;
				successor->left = target->left;
				root = successor;

			} else {
				successor = *successorParentPointer;
				*successorParentPointer = successor->right;
				successor->right = target->right;
				successor->left = target->left;
				root = successor;
			}
		}

	} else {
		parentPointerTarget = getBNodeParentAnFindTarget(root, key);

		if (NULL == parentPointerTarget) {
			printf("%s", "Not found\n");
			*status = B_TREE_NOT_FOUND;
			return root;
		}

		target = *parentPointerTarget;


		if ((NULL == target->left) && (NULL == target->right)) {
			*parentPointerTarget = NULL;

		} else if (NULL == target->left) {
			*parentPointerTarget = target->right;

		} else if (NULL == target->right) {
			*parentPointerTarget = target->left;

		} else {
			BNode*	successor = NULL;
			BNode** successorParentPointer = getBNodeParentOfLefter(target->right);

			if (NULL == successorParentPointer) {
				successor = target->right;

			} else {
				successor = *successorParentPointer;
				*successorParentPointer = successor->right;
				successor->right = target->right;
			}

			successor->left = target->left;
			*parentPointerTarget = successor;
		}
	}

	*status = B_TREE_REMOVE_SUCCESS;
	deleteOp(target);

	return root;
}
