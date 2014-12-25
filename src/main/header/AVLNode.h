#ifndef AVLNode_H
#define AVLNode_H

#include "Key.h"

typedef struct AVLNode AVLNode;

struct AVLNode {
    Key* key;
    unsigned char height;
    AVLNode* left;
    AVLNode* right;
} __attribute__((packed));

#endif
