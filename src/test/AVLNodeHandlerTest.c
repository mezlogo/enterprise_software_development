#include <stdlib.h>
#include "Key.h"
#include "Configuration.h"
#include "AVLNode.h"
#include "AVLNodeHandler.h"

#include "SimpleCUnit.h"

void test_case() {
    Key key1 = {1, 10};
    Key key3 = {3, 10};
    Key key4 = {4, 10};
    Key key5 = {5, 10};
    Key key6 = {6, 10};
    Key key7 = {7, 10};
    Key key9 = {9, 10};

    AVLNode node1 = {&key1, 1, NULL, NULL};
    AVLNode node4 = {&key4, 1, NULL, NULL};
    AVLNode node5 = {&key5, 1, NULL, NULL};
    AVLNode node6 = {&key6, 1, NULL, NULL};
    AVLNode node9 = {&key9, 1, NULL, NULL};

    AVLNode node3 = {&key3, 0, &node1, &node5};
    AVLNode node7 = {&key7, 0, &node3, &node9};

    Key key10 = {10, 10};
    AVLNode node10 = {&key10, 1, NULL, NULL};
    AVLNode* currentRoot;

    fixHeight(&node3);
    fixHeight(&node7);

    assertLongEquals("Fix height", 2, node3.height);
    assertLongEquals("Fix height", 3, node7.height);
    assertLongEquals("Tree is broken", (unsigned long) &node3, (unsigned long) node7.left);
    assertLongEquals("Tree is broken", (unsigned long) &node9, (unsigned long) node7.right);

    rotateRight(&node7);

    assertLongEquals("Tree is broken", (unsigned long) &node1, (unsigned long) node3.left);
    assertLongEquals("Tree is broken", (unsigned long) &node7, (unsigned long) node3.right);
    assertLongEquals("Tree is broken", (unsigned long) &node5, (unsigned long) node7.left);

    rotateLeft(&node3);

    assertLongEquals("Tree is broken", (unsigned long) &node3, (unsigned long) node7.left);
    assertLongEquals("Tree is broken", (unsigned long) &node9, (unsigned long) node7.right);

    node5.right = &node6;
    node5.left = &node4;
    fixHeight(&node5);
    fixHeight(&node3);
    fixHeight(&node7);

    assertLongEquals("Fix height", 2, node5.height);
    assertLongEquals("Fix height", 3, node3.height);
    assertLongEquals("Fix height", 4, node7.height);

    currentRoot = balance(&node7);
    assertLongEquals("Root changed", (unsigned long) currentRoot, (unsigned long) &node5);
    assertLongEquals("Fix height", 2, node7.height);
    assertLongEquals("Fix height", 3, node5.height);
    assertLongEquals("Tree is broken", (unsigned long) &node6, (unsigned long) node7.left);
    assertLongEquals("Tree is broken", (unsigned long) &node9, (unsigned long) node7.right);


    assertLongEquals("Fix height", 1, node9.height);

    currentRoot = insertAVLByNode(currentRoot, &node10);

    assertLongEquals("Fix height", 4, node5.height);
    assertLongEquals("Fix height", 2, node5.left->height);
    assertLongEquals("Fix height", 3, node5.right->height);
    assertLongEquals("Fix height", 2, node9.height);
    assertLongEquals("Tree is broken", (unsigned long) node9.right, (unsigned long) &node10);
    assertLongEquals("Tree is broken", (unsigned long) node9.left, (unsigned long) NULL);
    assertLongEquals("Tree is broken", (unsigned long) currentRoot, (unsigned long) &node5);

    void deleteOp(AVLNode * s) {
    }

    AVLNode* rmResult = removeAVLNode(&node5, &key10, &deleteOp);

    assertLongEquals("Tree is broken", (unsigned long) node9.right, (unsigned long) NULL);
    assertLongEquals("Tree is broken", (unsigned long) rmResult, (unsigned long) currentRoot);
    assertLongEquals("Tree is broken", (unsigned long) node9.left, (unsigned long) NULL);
    assertLongEquals("Fix height", 1, node9.height);
    assertLongEquals("Fix height", 3, node5.height);

    assertLongEquals("Tree is broken", (unsigned long) findAVLNode(currentRoot, node9.key), (unsigned long) &node9);

    Key missKey = {100, 0};
    assertLongEquals("Tree is broken", (unsigned long) findAVLNode(currentRoot, &missKey), (unsigned long) NULL);
    assertLongEquals("Tree is broken", (unsigned long) findAVLNode(currentRoot, &key10), (unsigned long) NULL);
}

int main(int argc, char** argv) {
    testSuit("AVL tree handler suit", 1,
	     initTestCase("Main test", &test_case)
	    );
    return 0;
}
