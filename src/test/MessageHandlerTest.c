#include "Key.h"
#include "MessageHandler.h"
#include "SimpleCUnit.h"

void test_case() {
	char msg[13];

	*(msg) = 1;	
	assertLongEquals("Should return right status 1", 1, getMessageStatus(msg) & 0xff);

	*(msg) = 190;
	assertLongEquals("Should return right status 190", 190, getMessageStatus(msg) & 0xff);

	*(msg) = 2;
	
	*(msg + 1) = 0x11;
	*(msg + 2) = 0x22;
	*(msg + 3) = 0x33;
	*(msg + 4) = 0x44;
	*(msg + 5) = 0x00;
	*(msg + 6) = 0xff;
	
	*(msg + 7) = 0x55;
	*(msg + 8) = 0x66;
	*(msg + 9) = 0x77;
	*(msg + 10) = 0x88;
	*(msg + 11) = 0xaa;
	*(msg + 12) = 0xee;
	
	Key primaryKey;
	Key secondaryKey;

	getPrimaryKey(&primaryKey, msg);
	getSecondKey(&secondaryKey, msg);
	
	assertLongEquals("Should return right status 2", 2, getMessageStatus(msg) & 0xff);
	
	assertLongEquals("Should return right primary ip", 0x44332211, primaryKey.ip);
	assertLongEquals("Should return right secondary ip", 0x88776655, secondaryKey.ip);
	assertLongEquals("Should return right primary port", 0xff00, primaryKey.port);
	assertLongEquals("Should return right secondary port", 0xeeaa, secondaryKey.port);
}

int main(int argc, char** argv) {
    testSuit("Message handler", 1,
	     initTestCase("Main case", &test_case));
    return 0;
}
