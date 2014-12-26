#include <stdio.h>
#include <stdlib.h>

#include "SimpleCUnit.h"
#include "Timer.h"

long res;

void test_getTime() {

	unsigned long start = getULongNano();

	res = 5 + (long) 5 * 60 * 100 * 8468 * 520 * 10;

	assertTrue("Calculation must take some time",
			   0 < calcOffsetULong(start));

}

void show() {
	int counter = 100;

	while (counter--) {
		unsigned long start = getULongNano();

		res = (long) 5 * 60 * 100 * 8468 * 520 * 10;

		printf("%s%lu\n", "Time: ",
			   calcOffsetULong(start));
	}

}


int main(int argc, char** argv) {
	show();
	/*testSuit("Timer test suit", 1,
		initTestCase("Just nano time to uint", &test_getTime)
		);*/

	return 0;
}
