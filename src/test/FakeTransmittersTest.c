#include "Key.h"
#include "FakeTransmitters.h"
#include "SimpleCUnit.h"


void test_case() {
	Key keys[2];

	keys[0].ip = 0x12345678;
	keys[0].port = 0x9abc;

	keys[1].ip = 0x87654321;
	keys[1].port = 0xfedc;

	setTransmitters(keys, 1);

	char message[17];
	char extraMessage[17];

	generateMessage(message, 1);

	char* msg = message;

	assertLongEquals("Returned msg should has regular type",
					 1, *msg & 0xff);
	assertLongEquals("Returned msg should eq what send",
					 0x78, msg[1] & 0xff);
	assertLongEquals("Returned msg should eq what send",
					 0x9a, msg[6] & 0xff);

	generateMessage(message, 0);
	generateMessage(extraMessage, 1);

	assertLongEquals("Returned msg should has alterHashTable type",
					 2, *msg & 0xff);
	assertLongEquals("Returned msg again should has regular type",
					 1, extraMessage[0] & 0xff);
	assertLongEquals("Returned msg should eq what send",
					 0x78, msg[1] & 0xff);
	assertLongEquals("Returned msg should eq what send",
					 0x9a, msg[6] & 0xff);

	assertLongEquals("Should return generated msg",
					 msg[7] & 0xff, extraMessage[1] & 0xff);
	assertLongEquals("Should return generated msg",
					 msg[8] & 0xff, extraMessage[2] & 0xff);
	assertLongEquals("Should return generated msg",
					 msg[12] & 0xff, extraMessage[6] & 0xff);

}


int main(int argc, char** argv) {
	testSuit("Fake transmitters suit", 1,
			 initTestCase("Main test case", &test_case)
			);
	return 0;
}
