#include <stdlib.h>
#include <stdio.h>

#include "Key.h"
#include "KeyHandler.h"
#include "AVLNode.h"

char height(AVLNode* root) {
	return NULL == root ? 0 : root->height;
}

char bfactor(AVLNode* root) {
	return height(root->right) - height(root->left);
}

void fixHeight(AVLNode* root) {
	char hl = height(root->left);
	char hr = height(root->right);
	root->height = (hr < hl ? hl : hr) + 1;
}

AVLNode* rotateRight(AVLNode* root) {
	AVLNode* q = root->left;
	root->left = q->right;
	q->right = root;
	fixHeight(root);
	fixHeight(q);
	return q;
}

AVLNode* rotateLeft(AVLNode* q) {
	AVLNode* root = q->right;
	q->right = root->left;
	root->left = q;
	fixHeight(q);
	fixHeight(root);
	return root;
}

AVLNode* balance(AVLNode* root) {
	fixHeight(root);

	if ( bfactor(root) == 2 ) {
		if ( bfactor(root->right) < 0 )
		{ root->right = rotateRight(root->right); }

		return rotateLeft(root);
	}

	if ( bfactor(root) == -2 ) {
		if ( bfactor(root->left) > 0  )
		{ root->left = rotateLeft(root->left); }

		return rotateRight(root);
	}

	return root;
}

AVLNode* insertAVLByNode(AVLNode* root, AVLNode* target) {
	if (NULL == root) { return target; }

	if (1 == compareKeys(root->key, target->key))
	{ root->left = insertAVLByNode(root->left, target); }

	else
	{ root->right = insertAVLByNode(root->right, target); }

	return balance(root);
}

AVLNode* findMin(AVLNode* root) {
	return NULL != root->left ? findMin(
			   root->left) : root;
}

AVLNode* removeMin(AVLNode* root) {
	if (NULL == root->left)
	{ return root->right; }

	root->left = removeMin(root->left);
	return balance(root);
}

AVLNode* removeAVLNode(AVLNode* root, Key* key, void (*deleteOp)(AVLNode*)) {
	if (NULL == root) { return NULL; }

	if (NULL == key) { return root; }

	switch (compareKeys(root->key, key)) {
	case 1: {
			root->left = removeAVLNode(root->left, key,
									   deleteOp);
		}
		break;

	case -1: {
			root->right = removeAVLNode(root->right, key,
										deleteOp);
		}
		break;

	case 0: {
			AVLNode* left = root->left;
			AVLNode* right = root->right;

			deleteOp(root);

			if (NULL == right) { return left; }

			AVLNode* min = findMin(right);
			min->right = removeMin(right);
			min->left = left;
			return balance(min);
		}
		break;

	default:
		printf("%s", "Compare error!\n");
	}

	return balance(root);
}

AVLNode* findAVLNode(AVLNode* root, Key* key) {
	if (NULL == root) { return NULL; }

	AVLNode* result;

	switch (compareKeys(root->key, key)) {
	case 1: {
			result = findAVLNode(root->left, key);
		}
		break;

	case -1: {
			result = findAVLNode(root->right, key);
		}
		break;

	case 0: {
			result = root;
		}
		break;

	default:
		printf("%s", "Compare error!\n");
	}

	return result;
}
