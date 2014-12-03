#include <stdio.h>
#include <stdlib.h>
#include <Random.h>

int main(int argc, char **argv) {
	int i = 100;
	
	char cnt = 0;
	
	while(i--)
		if (generateInt() % 2)
			cnt++;
	
	printf("%d\n", cnt);
	
	//testSuit("Multi thread handler suit", 1, initTestCase("Multi thread starting", &test_multiThreadStart));
    return 0;
}
