#include "Key.h"
#include "AVLNode.h"

char height(AVLNode* p);
char bfactor(AVLNode* p);
void fixHeight(AVLNode* p);
AVLNode* rotateRight(AVLNode* p);
AVLNode* rotateLeft(AVLNode* q);
AVLNode* balance(AVLNode* p);
AVLNode* insertAVLByNode(AVLNode* root,
						 AVLNode* target);
AVLNode* removeAVLNode(AVLNode* root, Key* key,
					   void (*deleteOp)(AVLNode*));
AVLNode* findAVLNode(AVLNode* root, Key* key);
