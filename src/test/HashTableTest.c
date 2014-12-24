#include <stdlib.h>
#include "Key.h"
#include "Configuration.h"
#include "LinkedListNode.h"
#include "LinkedListHandler.h"
#include "HashTable.h"

#include "MemoryManagerSubheap.h"

#include "SimpleCUnit.h"

#define initMM(nodesCount)	/*int variablesSize[3] = {sizeof(Key), sizeof(LinkedListNode), nodesCount * sizeof(LinkedListNode*)};	int variablesCount[3] = {nodesCount, nodesCount, 1};	char subheapCount = 3;	assertLongEquals("Should init memory manager", INITIAL_SUCCESS, init(variablesSize, variablesCount, subheapCount)); assertLongEquals("Shouldn't init hash table", HASH_TABLE_INIT_FAIL, initHashTable(nodesCount + 1));*/ 	assertLongEquals("Should init hash table", HASH_TABLE_INIT_SUCCESS, initHashTable(nodesCount));

void test_alterHashTable() {
    int nodesCount = 4;
    initMM(nodesCount);

    Key key1 = {0xa0101123, 0x6981};
    Key key2 = {0xa0001122, 0x6981};
    Key key3 = {0xa000f122, 0x0081};
    Key key4 = {0xa000f122, 0x0058};
    Key key5 = {0xa000f122, 0x3256};

    assertLongEquals("Should insert", INSERT_SUCCESS, insertHashTable(&key1));
    assertLongEquals("Should insert", INSERT_SUCCESS, insertHashTable(&key2));
    assertLongEquals("Should insert", INSERT_SUCCESS, insertHashTable(&key3));
    assertLongEquals("Should insert", INSERT_SUCCESS, insertHashTable(&key4));

    assertLongEquals("Shouldn't insert", INSERT_FAIL, insertHashTable(&key5));

    assertLongEquals("Shouldn find", FIND_SUCCESS, findHashTable(&key1));
    assertLongEquals("Shouldn find", FIND_SUCCESS, findHashTable(&key2));
    assertLongEquals("Shouldn find", FIND_SUCCESS, findHashTable(&key3));
    assertLongEquals("Shouldn find", FIND_SUCCESS, findHashTable(&key4));

    key4.ip = 3;
    key3.port = 0;

    assertLongEquals("Shouldn't find", FIND_FAIL, findHashTable(NULL));
    assertLongEquals("Shouldn't find", FIND_FAIL, findHashTable(&key5));
    assertLongEquals("Shouldn't find", FIND_FAIL, findHashTable(&key4));
    assertLongEquals("Shouldn't find", FIND_FAIL, findHashTable(&key3));

    assertLongEquals("Should alterHashTable", ALTER_SUCCESS, alterHashTable(&key1, &key5));
    assertLongEquals("Shouldn find", FIND_SUCCESS, findHashTable(&key5));
    assertLongEquals("Shouldn't find", FIND_FAIL, findHashTable(&key1));

    assertLongEquals("Shouldn remove", REMOVE_SUCCESS, alterHashTable(&key5, NULL));
    assertLongEquals("Shouldn't find", FIND_FAIL, findHashTable(&key5));

    assertLongEquals("Shouldn't alterHashTable", ALTER_FAIL, alterHashTable(NULL, &key2));
    assertLongEquals("Shouldn't alterHashTable", ALTER_FAIL, alterHashTable(&key5, &key3));
}

void test_find() {
    int nodesCount = 10;
    initMM(nodesCount);

    Key key1 = {0xabcdef01, 0x6981};
    Key key2 = {0xa0001123, 0x6981};
    Key key3 = {0xabcdef01, 0x0000};

    assertLongEquals("Should insert", INSERT_SUCCESS, insertHashTable(&key1));
    assertLongEquals("Should insert", INSERT_SUCCESS, insertHashTable(&key2));

    assertLongEquals("Should find", FIND_SUCCESS, findHashTable(&key1));
    assertLongEquals("Shouldn't find", FIND_FAIL, findHashTable(&key3));
    assertLongEquals("Shouldn't find", FIND_FAIL, findHashTable(NULL));
}

void test_insert() {
    int nodesCount = 10;
    initMM(nodesCount);

    Key key = {0xabcdef01, 0x6981};

    while (nodesCount--) {
	assertLongEquals("Should inser", INSERT_SUCCESS, insertHashTable(&key));
    }
    assertLongEquals("Shouldn't insert", INSERT_FAIL, insertHashTable(&key));
}

int main(int argc, char** argv) {
    testSuit("Hash table suit", 3,
	     initTestCase("Find test", &test_insert),
	     initTestCase("Inser test", &test_find),
	     initTestCase("Alter test", &test_alterHashTable)
	    );
    return 0;
}
