#include <stdio.h>
#include <stdlib.h>

#include "SimpleCUnit.h"
#include "Timer.h"


void test_getTime(){
	
	unsigned int start = getUIntNano();
		
	long res = 5 + (long) 5*60*100*8468*520*10;
		
	assertTrue("Calculation must take some time", 0 < calcOffsetUInt(start));
}



int main(int argc, char **argv) {

	testSuit("Timer test suit", 1, 
		initTestCase("Just nano time to uint", &test_getTime)
		);

    return 0;
}
