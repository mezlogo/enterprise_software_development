#include <stdlib.h>

#include "Key.h"
#include "Configuration.h"
#include "BNode.h"
#include "BNodeHandler.h"
#include "BTree.h"

#include "MemoryManagerSubheap.h"

#include "SimpleCUnit.h"

#define initMM(nodesCount)	assertLongEquals("Should init B tree", HASH_TABLE_INIT_SUCCESS, initBTree(nodesCount));

void test_alter() {
	/*int nodesCount = 4;
	initMM(nodesCount);

	Key key1 = {1, 10};
	Key key2 = {2, 0x6981};
	Key key3 = {3, 0x0081};
	Key key4 = {4, 0x0058};
	Key key5 = {5, 0x3256};

	assertLongEquals("Should insert", INSERT_SUCCESS,
					 insertBTree(&key1));
	assertLongEquals("Should insert", INSERT_SUCCESS,
					 insertBTree(&key2));
	assertLongEquals("Should insert", INSERT_SUCCESS,
					 insertBTree(&key3));
	assertLongEquals("Should insert", INSERT_SUCCESS,
					 insertBTree(&key4));

	assertLongEquals("Shouldn't insert", INSERT_FAIL,
					 insertBTree(&key5));

	assertLongEquals("Should find", FIND_SUCCESS,
					 findBTree(&key1));
	assertLongEquals("Should find", FIND_SUCCESS,
					 findBTree(&key2));
	assertLongEquals("Should find", FIND_SUCCESS,
					 findBTree(&key3));
	assertLongEquals("Should find", FIND_SUCCESS,
					 findBTree(&key4));

	key4.ip = 3;
	key3.port = 0;

	assertLongEquals("Shouldn't find", FIND_FAIL,
					 findBTree(NULL));
	assertLongEquals("Shouldn't find", FIND_FAIL,
					 findBTree(&key5));
	assertLongEquals("Shouldn't find", FIND_FAIL,
					 findBTree(&key4));
	assertLongEquals("Shouldn't find", FIND_FAIL,
					 findBTree(&key3));

	assertLongEquals("Should alterBTree",
					 ALTER_SUCCESS, alterBTree(&key1, &key5));
	assertLongEquals("Shouldn find", FIND_SUCCESS,
					 findBTree(&key5));
	assertLongEquals("Shouldn't find", FIND_FAIL,
					 findBTree(&key1));

	assertLongEquals("Shouldn remove", REMOVE_SUCCESS,
					 alterBTree(&key5, NULL));
	assertLongEquals("Shouldn't find", FIND_FAIL,
					 findBTree(&key5));

	assertLongEquals("Shouldn't alterBTree",
					 ALTER_FAIL, alterBTree(NULL, &key2));
	assertLongEquals("Shouldn't alterBTree",
					 ALTER_SUCCESS, alterBTree(&key5, &key3));*/
}
void test_find() {
	int nodesCount = 10;
	initMM(nodesCount);

	Key key1 = {0xabcdef01, 0x6981};
	Key key2 = {0xa0001123, 0x6981};
	Key key3 = {0xabcdef01, 0x0000};

	assertLongEquals("Shouldn't find", FIND_FAIL, findBTree(&key3));
	assertLongEquals("Should insert", INSERT_SUCCESS, insertBTree(&key1));
	assertLongEquals("Should insert", INSERT_SUCCESS, insertBTree(&key2));

	assertLongEquals("Should find", FIND_SUCCESS, findBTree(&key1));
	assertLongEquals("Shouldn't find", FIND_FAIL, findBTree(&key3));
	assertLongEquals("Shouldn't find", FIND_FAIL, findBTree(NULL));
}

void test_insert() {
	initMM(4);

	Key key1 = {0xabcdea01, 0x6981};
	Key key2 = {0xabcde000, 0x6981};
	Key key3 = {0xabcded02, 0x6981};
	Key key4 = {0xabcdef03, 0x6981};
	Key key5 = {0xabcdec04, 0x6981};

	assertLongEquals("Shouldn't insert", INSERT_FAIL, insertBTree(NULL));

	assertLongEquals("Should inser", INSERT_SUCCESS, insertBTree(&key1));

	assertLongEquals("Shouldn't insert", INSERT_FAIL, insertBTree(&key1));

	assertLongEquals("Should inser", INSERT_SUCCESS, insertBTree(&key2));
	assertLongEquals("Should inser", INSERT_SUCCESS, insertBTree(&key3));
	assertLongEquals("Should inser", INSERT_SUCCESS, insertBTree(&key4));

	assertLongEquals("Shouldn't insert", INSERT_FAIL, insertBTree(&key5));
}

int main(int argc, char** argv) {
	testSuit("B tree suit", 3,
			 initTestCase("Insert test", &test_insert),
			 initTestCase("Find test", &test_find),
			 initTestCase("Alter test", &test_alter)
			);
	return 0;
}
