#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "ErrorCode.h"
#include "MultiThreadHandler.h"
#include "SimpleCUnit.h"

pthread_mutex_t locka;
pthread_mutex_t lockb;

void child(){
	pthread_mutex_lock(&locka);
	pthread_mutex_lock(&lockb);
	
	printf("%s", "Hello test, from child!\n");
	
	pthread_mutex_lock(&locka);
	pthread_mutex_lock(&lockb);
	
	printf("%s", "Hello test, from child!\n");
	
}

long parent(){
	pthread_mutex_lock(&lockb);
	pthread_mutex_lock(&locka);
	
	printf("%s", "Hello test, from parent!\n");
	
	pthread_mutex_lock(&lockb);
	pthread_mutex_lock(&locka);
	
	printf("%s", "Hello test, from parent!\n");
	
	return 1;
}

void test_multiThreadStart() {
	assertTrue("Should return 1", 1 == multiThreadStart(&parent, &child));
}


int main(int argc, char **argv) {
	pthread_mutex_init(&locka, NULL);
	pthread_mutex_init(&lockb, NULL);
	testSuit("Multi thread handler suit", 1, 
		initTestCase("Should sync", &test_multiThreadStart)		
	);
    return 0;
}
