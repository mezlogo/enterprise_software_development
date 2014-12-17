#ifndef AVLNode_H
#define AVLNode_H

#include "Key.h"

typedef struct AVLNode { // структура для представления узлов дерева
    Key key;
    unsigned char height;
    node* left;
    node* right;
    node(Key k) { key = k; left = right = 0; height = 1; }
} AVLNode;

#endif
