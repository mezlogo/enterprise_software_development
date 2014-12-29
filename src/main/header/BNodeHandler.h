#include "Key.h"
#include "BNode.h"

BNode* findBNodeInsideRoot(BNode* root, Key* key);
BNode** getBNodeParentAnFindTarget(BNode* root, Key* key);
BNode** getBNodeParentOfLefter(BNode* root);
char insertBNodeInsideRoot(BNode* root, BNode* target);
BNode* deleteBNodeFromRoot(BNode* root, Key* key,  void (*deleteOp)(BNode*));
