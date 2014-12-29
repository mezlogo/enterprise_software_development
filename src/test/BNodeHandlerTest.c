#include <stdlib.h>
#include "Key.h"
#include "Configuration.h"
#include "BNode.h"
#include "BNodeHandler.h"

#include "SimpleCUnit.h"

void test_case() {
	Key key1 = {1, 10};
	Key key2 = {2, 10};
	Key key3 = {3, 10};
	Key key4 = {4, 10};
	Key key5 = {5, 10};

	BNode node1 = {&key1};
	BNode node2 = {&key2};
	BNode node3 = {&key3};
	BNode node4 = {&key4};
	BNode node5 = {&key5};

	assertLongEquals("Should be eq", (unsigned long) &node1, (unsigned long) findBNodeInsideRoot(&node1,
					 &key1));
	assertLongEquals("Shouldn't be eq", (unsigned long) NULL,
					 (unsigned long) findBNodeInsideRoot(&node1, &key2));
	assertLongEquals("Shouldn't be eq", (unsigned long) NULL,
					 (unsigned long) findBNodeInsideRoot(&node1, NULL));
	/* 		2
	 * 1		4*/
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node1));
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node4));
	assertLongEquals("Shouldn't insert",  TREE_INSERT_NOT_UNIQ, insertBNodeInsideRoot(&node2, &node1));

	assertLongEquals("Should be eq", (unsigned long) &node1, (unsigned long) findBNodeInsideRoot(&node2,
					 &key1));
	assertLongEquals("Should be eq", (unsigned long) &node4, (unsigned long) findBNodeInsideRoot(&node2,
					 &key4));

	assertLongEquals("Should be eq", (unsigned long) &node4, (unsigned long) node2.right);
	assertLongEquals("Should be eq", (unsigned long) &node1, (unsigned long) node2.left);

	/* 		2
	 * 1		4
	 * 		3		5*/
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node3));
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node5));

	assertLongEquals("Should be eq", (unsigned long) &node5, (unsigned long) node4.right);
	assertLongEquals("Should be eq", (unsigned long) &node3, (unsigned long) node4.left);

	assertLongEquals("Should be eq", (unsigned long) &node5, (unsigned long) findBNodeInsideRoot(&node2,
					 &key5));
	assertLongEquals("Should be eq", (unsigned long) &node3, (unsigned long) findBNodeInsideRoot(&node2,
					 &key3));

	BNode** pointerToTarget = getBNodeParentAnFindTarget(&node2, &key3);
	BNode* target = *pointerToTarget;

	assertLongEquals("Should be eq", (unsigned long) &node3, (unsigned long) *pointerToTarget);
	assertLongEquals("Should be eq", (unsigned long) &node3, (unsigned long) target);

	assertLongEquals("Should be eq", (unsigned long) &node5,
					 (unsigned long) *getBNodeParentAnFindTarget(&node2, &key5));
	assertLongEquals("Should be eq", (unsigned long) NULL,
					 (unsigned long) getBNodeParentAnFindTarget(&node2, &key2));
	assertLongEquals("Should be eq", (unsigned long) NULL,
					 (unsigned long) getBNodeParentAnFindTarget(&node1, &key1));
	assertLongEquals("Should be eq", (unsigned long) NULL,
					 (unsigned long) getBNodeParentAnFindTarget(&node4, &key1));

	assertLongEquals("Should be eq", (unsigned long) &node3,
					 (unsigned long) *getBNodeParentOfLefter(&node4));

	assertLongEquals("Should be eq", (unsigned long) &node1,
					 (unsigned long) *getBNodeParentOfLefter(&node2));

	assertLongEquals("Should be eq", (unsigned long) NULL,
					 (unsigned long) getBNodeParentOfLefter(NULL));
	assertLongEquals("Should be eq", (unsigned long) NULL,
					 (unsigned long) getBNodeParentOfLefter(&node1));
	assertLongEquals("Should be eq", (unsigned long) NULL,
					 (unsigned long) getBNodeParentOfLefter(&node3));
	assertLongEquals("Should be eq", (unsigned long) NULL,
					 (unsigned long) getBNodeParentOfLefter(&node5));

	char rmStatus = 0;
	int counter = 0;
	void deleteOp(BNode * toDeleete) {
		counter++;
	}
	assertLongEquals("Should be eq", (unsigned long) NULL, (unsigned long) deleteBNodeFromRoot(&node1,
					 &key1,  &deleteOp, &rmStatus));
	assertLongEquals("Should be eq", B_TREE_REMOVE_SUCCESS, rmStatus);
	/* 		3
	 * 1		4
	 * 				5*/

	BNode* currentRoot = deleteBNodeFromRoot(&node2, &key2,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", (unsigned long) &node3, (unsigned long) currentRoot);
	assertLongEquals("Should be eq", (unsigned long) &node1, (unsigned long) currentRoot->left);
	assertLongEquals("Should be eq", (unsigned long) &node4, (unsigned long) currentRoot->right);

	/* 		4
	 * 1		5*/
	currentRoot = deleteBNodeFromRoot(&node3, &key3,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", (unsigned long) &node4, (unsigned long) currentRoot);
	assertLongEquals("Should be eq", (unsigned long) &node1, (unsigned long) currentRoot->left);
	assertLongEquals("Should be eq", (unsigned long) &node5, (unsigned long) currentRoot->right);
	assertLongEquals("Should be eq", (unsigned long) NULL, (unsigned long) findBNodeInsideRoot(&node4,
					 &key2));
	assertLongEquals("Should be eq", (unsigned long) NULL, (unsigned long) findBNodeInsideRoot(&node4,
					 &key3));

	/* 		4
	 *  		5*/
	currentRoot = deleteBNodeFromRoot(&node4, &key1,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", (unsigned long) &node4, (unsigned long) currentRoot);
	assertLongEquals("Should be eq", (unsigned long) NULL, (unsigned long) currentRoot->left);
	assertLongEquals("Should be eq", (unsigned long) &node5, (unsigned long) currentRoot->right);

	/* 		5*/
	currentRoot = deleteBNodeFromRoot(&node4, &key4,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", (unsigned long) &node5, (unsigned long) currentRoot);
	assertLongEquals("Should be eq", (unsigned long) NULL, (unsigned long) currentRoot->left);
	assertLongEquals("Should be eq", (unsigned long) NULL, (unsigned long) currentRoot->right);


	/* 		5
	 * 4 		 */
	node4.left = NULL;
	node4.right = NULL;
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node5, &node4));

	/* 		4*/
	currentRoot = deleteBNodeFromRoot(&node5, &key5,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", (unsigned long) &node4, (unsigned long) currentRoot);
	assertLongEquals("Should be eq", (unsigned long) NULL, (unsigned long) currentRoot->left);
	assertLongEquals("Should be eq", (unsigned long) NULL, (unsigned long) currentRoot->right);


	/* 		2
	 * 1 	     5
	 * 		 3     6
	 * 		   4	*/
	Key key6 = {6, 10};
	BNode node6 = {&key6};

#define RESET_NODE(node) node.left = NULL; node.right = NULL;
	RESET_NODE(node1)
	RESET_NODE(node2)
	RESET_NODE(node3)
	RESET_NODE(node4)
	RESET_NODE(node5)

	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node1));
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node5));
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node3));
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node6));
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node4));

	assertLongEquals("Should be eq", (unsigned long) &node4, (unsigned long) node3.right);
	assertLongEquals("Should be eq", (unsigned long) &node6, (unsigned long) node5.right);
	assertLongEquals("Should be eq", (unsigned long) &node3, (unsigned long) node5.left);

	currentRoot = deleteBNodeFromRoot(&node2, &key5,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", (unsigned long) &node2, (unsigned long) currentRoot);
	assertLongEquals("Should be eq", (unsigned long) &node6, (unsigned long) currentRoot->right);

	/* 		2
	 * 1 	     6
	 * 		 3
	 * 		   4	*/
	RESET_NODE(node5)
	RESET_NODE(node6)
	Key key7 = {7, 10};
	BNode node7 = {&key7};
	Key key8 = {8, 10};
	BNode node8 = {&key8};
	/* 		2
	 * 1 	     5
	 * 		 3     	  8
	 * 		   4   6
	 * 			     7     */
	node2.right = &node5;
	node5.left 	= &node3;
	//node5.right = &node8;
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node8));
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node6));
	assertLongEquals("Should insert",  TREE_INSERT_OK, insertBNodeInsideRoot(&node2, &node7));

	assertLongEquals("Should be eq", (unsigned long) &node3, (unsigned long) node5.left);
	assertLongEquals("Should be eq", (unsigned long) &node8, (unsigned long) node5.right);
	assertLongEquals("Should be eq", (unsigned long) &node6, (unsigned long) node8.left);
	assertLongEquals("Should be eq", (unsigned long) &node7, (unsigned long) node6.right);

	/* 		2
	 * 1 	     6
	 * 		 3     	  8
	 * 		   4   7 */
	currentRoot = deleteBNodeFromRoot(&node2, &key5,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", (unsigned long) &node2, (unsigned long) currentRoot);
	assertLongEquals("Should be eq", (unsigned long) &node8, (unsigned long) node6.right);
	assertLongEquals("Should be eq", (unsigned long) &node6, (unsigned long) currentRoot->right);

	/* 		2
	 * 1 	     6
	 * 		 4     	  8
	 * 		       7 */
	currentRoot = deleteBNodeFromRoot(&node2, &key3,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", (unsigned long) &node4, (unsigned long) node6.left);
	/* 		2
	 * 1 	     6
	 * 		 4     	  7*/
	currentRoot = deleteBNodeFromRoot(&node2, &key8,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", (unsigned long) &node7, (unsigned long) node6.right);
	assertLongEquals("Should be eq", B_TREE_REMOVE_SUCCESS, rmStatus);

	assertLongEquals("Should be eq", 10, counter);

	deleteBNodeFromRoot(&node2, &key3,  &deleteOp, &rmStatus);
	assertLongEquals("Should be eq", B_TREE_NOT_FOUND, rmStatus);

}


int main(int argc, char** argv) {
	testSuit("B tree handler suit", 1,
			 initTestCase("Main test", &test_case)
			);
	return 0;
}
