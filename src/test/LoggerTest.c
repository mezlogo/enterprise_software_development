#include "Configuration.h"
#include "Logger.h"
#include "SimpleCUnit.h"

void test_case() {
	reset();
	logAllocate(20);
	logAllocate(1);
	logAllocate(320);
	logAllocate(220);
	logRemove(110);
	logRemove(21);
	logRemove(155);
	logRemove(1);
	logRemove(8);
	show();
	
	reset();
	logRemove(1559);
	logRemove(154);
	logAllocate(208);
	logAllocate(19);
	logRemove(825);
	show();
}

int main(int argc, char **argv) {
	testSuit("Logger suit", 1,	
		initTestCase("Logger case", &test_case)		
	);
    return 0;
}
