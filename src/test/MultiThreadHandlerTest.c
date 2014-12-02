#include <stdio.h>
#include <stdlib.h>
#include "ErrorCode.h"
#include "MultiThreadHandler.h"
#include "SimpleCUnit.h"

void child(){
	printf("%s", "Hello test, from child!\n");
}

long parent(){
	return 1;
}

void test_multiThreadStart() {
	assertTrue("Should return 1", 1 == multiThreadStart(&parent, &child));
}


int main(int argc, char **argv) {
	testSuit("Multi thread handler suit", 1, 
		initTestCase("Multi thread starting", &test_multiThreadStart)		
	);
    return 0;
}
