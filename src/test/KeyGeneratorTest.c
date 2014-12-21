#include "Key.h"
#include "KeyGenerator.h"
#include "SimpleCUnit.h"

void test_generateKey() {
    Key key = {6900000, 10};

    assertLongEquals("Ip should eq init val", 6900000, key.ip);
    assertLongEquals("Port should eq init val", 10, key.port);

    generateKey(&key);

    assertTrue("Ip shouldn't eq init val", 6900000 != key.ip);
    assertTrue("Port shouldn't eq init val", 10 != key.port);
}


void initKey(Key* key, unsigned int ip, unsigned short port) {
    key->ip = ip;
    key->port = port;
}

void test_isUniq() {
    Key keys[4];
    initKey(&keys[0], 10, 10);
    initKey(&keys[1], 100, 10);
    initKey(&keys[2], 10, 100);
    initKey(&keys[3], 100, 100);

    Key key = {100, 100};

    assertLongEquals("Isn't uniq, cos first eq last", 1, isUniq(&key, keys, 4));
    assertLongEquals("Is uniq, cos take without last", 0, isUniq(&key, keys, 3));

    key.port = 1;
    assertLongEquals("Should be uniq", 0, isUniq(&key, keys, 4));
}

void test_generateUniqKeys() {
    Key keys[1000];
    int length = 1000;
    int count = 0;

    generateUniqKeys(keys, length);

    do {
	assertLongEquals("Should be uniq", 0, isUniq(&keys[count], keys, count - 1));
    } while (++count < length);
}


int main(int argc, char** argv) {
    testSuit("Key generator suit", 3,
	     initTestCase("Key generate test", &test_generateKey),
	     initTestCase("Is key uniq test", &test_isUniq),
	     initTestCase("Uniq key generate test", &test_generateUniqKeys));
    return 0;
}
