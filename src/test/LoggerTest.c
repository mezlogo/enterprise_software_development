#include "Configuration.h"
#include "Logger.h"
#include "SimpleCUnit.h"

void test_case() {

	reset();
	logPrimary(20);
	logPrimary(1);
	logPrimary(320);
	logPrimary(220);
	logSecondary(110);
	logSecondary(21);
	logSecondary(155);
	logSecondary(1);
	logSecondary(8);
	show("Console test");

	reset();
	logSecondary(1559);
	logSecondary(154);
	logPrimary(208);
	logPrimary(19);
	logSecondary(825);
	setFileLoggerOutput();
	show("Second file test");
}

int main(int argc, char** argv) {
	testSuit("Logger suit", 1,
			 initTestCase("Logger case", &test_case)
			);
	return 0;
}
