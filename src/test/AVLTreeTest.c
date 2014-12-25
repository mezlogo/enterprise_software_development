#include <stdlib.h>

#include "Key.h"
#include "Configuration.h"
#include "AVLNode.h"
#include "AVLNodeHandler.h"
#include "AVLTree.h"

#include "MemoryManagerSubheap.h"

#include "SimpleCUnit.h"

#define initMM(nodesCount)	assertLongEquals("Should init AVL tree", HASH_TABLE_INIT_SUCCESS, initAVLTree(nodesCount));

void test_alter() {
    int nodesCount = 4;
    initMM(nodesCount);

    Key key1 = {1, 10};
    Key key2 = {2, 0x6981};
    Key key3 = {3, 0x0081};
    Key key4 = {4, 0x0058};
    Key key5 = {5, 0x3256};

    assertLongEquals("Should insert", INSERT_SUCCESS, insertAVLTree(&key1));
    assertLongEquals("Should insert", INSERT_SUCCESS, insertAVLTree(&key2));
    assertLongEquals("Should insert", INSERT_SUCCESS, insertAVLTree(&key3));
    assertLongEquals("Should insert", INSERT_SUCCESS, insertAVLTree(&key4));

    assertLongEquals("Shouldn't insert", INSERT_FAIL, insertAVLTree(&key5));

    assertLongEquals("Should find", FIND_SUCCESS, findAVLTree(&key1));
    assertLongEquals("Should find", FIND_SUCCESS, findAVLTree(&key2));
    assertLongEquals("Should find", FIND_SUCCESS, findAVLTree(&key3));
    assertLongEquals("Should find", FIND_SUCCESS, findAVLTree(&key4));

    key4.ip = 3;
    key3.port = 0;

    assertLongEquals("Shouldn't find", FIND_FAIL, findAVLTree(NULL));
    assertLongEquals("Shouldn't find", FIND_FAIL, findAVLTree(&key5));
    assertLongEquals("Shouldn't find", FIND_FAIL, findAVLTree(&key4));
    assertLongEquals("Shouldn't find", FIND_FAIL, findAVLTree(&key3));

    assertLongEquals("Should alterAVLTree", ALTER_SUCCESS, alterAVLTree(&key1, &key5));
    assertLongEquals("Shouldn find", FIND_SUCCESS, findAVLTree(&key5));
    assertLongEquals("Shouldn't find", FIND_FAIL, findAVLTree(&key1));

    assertLongEquals("Shouldn remove", REMOVE_SUCCESS, alterAVLTree(&key5, NULL));
    assertLongEquals("Shouldn't find", FIND_FAIL, findAVLTree(&key5));

    assertLongEquals("Shouldn't alterAVLTree", ALTER_FAIL, alterAVLTree(NULL, &key2));
    assertLongEquals("Shouldn't alterAVLTree", ALTER_SUCCESS, alterAVLTree(&key5, &key3));
}
void test_find() {
    int nodesCount = 10;
    initMM(nodesCount);

    Key key1 = {0xabcdef01, 0x6981};
    Key key2 = {0xa0001123, 0x6981};
    Key key3 = {0xabcdef01, 0x0000};

    assertLongEquals("Should insert", INSERT_SUCCESS, insertAVLTree(&key1));
    assertLongEquals("Should insert", INSERT_SUCCESS, insertAVLTree(&key2));

    assertLongEquals("Should find", FIND_SUCCESS, findAVLTree(&key1));
    assertLongEquals("Shouldn't find", FIND_FAIL, findAVLTree(&key3));
    assertLongEquals("Shouldn't find", FIND_FAIL, findAVLTree(NULL));
}


void test_insert() {
    int nodesCount = 10000;
    initMM(nodesCount);

    Key key = {0xabcdef01, 0x6981};

    assertLongEquals("Shouldn't insert", INSERT_FAIL, insertAVLTree(NULL));

    while (nodesCount--) {
	assertLongEquals("Should inser", INSERT_SUCCESS, insertAVLTree(&key));
    }
    assertLongEquals("Shouldn't insert", INSERT_FAIL, insertAVLTree(&key));
}

int main(int argc, char** argv) {
    testSuit("AVL tree suit", 3,
	     initTestCase("Insert test", &test_insert),
	     initTestCase("Find test", &test_find),
	     initTestCase("Alter test", &test_alter)
	    );
    return 0;
}
