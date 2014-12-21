#include "Key.h"
#include "KeyHandler.h"
#include "SimpleCUnit.h"

//char compareKeys(Key * key1, Key * key2)
//unsigned int hashCode(Key * key)
//void keyToCharArray(Key * key, char * array)

void test_keyToCharArray() {
    Key key = {0x02468ace, 0x1379};

    char array[10];

    keyToCharArray(&key, &array[1]);

    assertLongEquals("First should eq last ip byte", 0xce, array[1] & 0xff);
    assertLongEquals("Second should eq pre last ip byte", 0x8a, array[2]  & 0xff);
    assertLongEquals("Third should eq after first ip byte", 0x46, array[3]  & 0xff);
    assertLongEquals("Fourth should eq first ip byte", 0x02, array[4]  & 0xff);
    assertLongEquals("Fifth should eq last port byte", 0x79, array[5]  & 0xff);
    assertLongEquals("Sixth should eq first port byte", 0x13, array[6]  & 0xff);
}

void test_hashCode() {
    Key key = {6900000, 10};

    assertLongEquals("Hash should eq ip", 6900000, hashCode(&key));
}

void test_compareKeys() {
    Key key1 = {100, 10};
    Key key2 = {100, 10};
    assertLongEquals("Compare should eq", 0, compareKeys(&key1, &key2));

    key1.ip = 99;
    assertLongEquals("Firs Keyk is less (ip less)", -1, compareKeys(&key1, &key2));

    key1.port = 9;
    assertLongEquals("Firs Keyk is less (ip less port less)", -1, compareKeys(&key1, &key2));

    key1.port = 11;
    assertLongEquals("Firs Keyk is less (ip less port greater)", -1, compareKeys(&key1, &key2));

    key1.ip = 100;
    key1.port = 10;
    assertLongEquals("Compare should eq", 0, compareKeys(&key1, &key2));

    key1.port = 9;
    assertLongEquals("Firs Keyk is less (ip eq port less)", -1, compareKeys(&key1, &key2));

    key1.ip = 100;
    key1.port = 10;
    assertLongEquals("Compare should eq", 0, compareKeys(&key1, &key2));

    key1.port = 11;
    assertLongEquals("Firs Keyk is greater (ip eq port greater)", 1, compareKeys(&key1, &key2));

    key1.ip = 101;
    key1.port = 11;
    assertLongEquals("Firs Keyk is greater (ip greater port greater)", 1, compareKeys(&key1, &key2));

    key1.port = 10;
    assertLongEquals("Firs Keyk is greater (ip greater port eq)", 1, compareKeys(&key1, &key2));

    key1.port = 9;
    assertLongEquals("Firs Keyk is greater (ip greater port less)", 1, compareKeys(&key1, &key2));
}

int main(int argc, char** argv) {
    testSuit("Key handler suit", 3,
	     initTestCase("Hash code test", &test_hashCode),
	     initTestCase("Key to char array test", &test_keyToCharArray),
	     initTestCase("Compare test", &test_compareKeys));
    return 0;
}
