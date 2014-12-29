#ifndef BNode_H
#define BNode_H

#include "Key.h"

typedef struct BNode BNode;

struct BNode {
	Key* key;
	BNode* left;
	BNode* right;
};

#endif
