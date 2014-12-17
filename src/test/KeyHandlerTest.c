#include "Key.h"
#include "KeyHandler.h"
#include "SimpleCUnit.h"

//char compareKeys(Key * key1, Key * key2)
//unsigned int hashCode(Key * key)

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
    testSuit("Key handler suit", 2,
	     initTestCase("Hash code test", &test_hashCode),
	     initTestCase("Compare test", &test_compareKeys));
    return 0;
}
