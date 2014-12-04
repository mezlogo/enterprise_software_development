#include <stdio.h>
#include <stdlib.h>

#include <pthread.h>

#include "ErrorCode.h"
#include "MultiThreadHandler.h"
#include "SimpleCUnit.h"

pthread_mutex_t locka;
pthread_mutex_t lockb;

void child(){
	printf("child locka = %x\n", &locka);
	printf("child before mutex A locking\n");
	int a = pthread_mutex_lock(&locka);
	printf("mutex A locked by child\n");
	int b =-1;// = pthread_mutex_unlock(&lockb);
	
	printf("%s%d%s%d\n", "Child lock a: ", a, " unlock b: ", b);
	
	a = pthread_mutex_lock(&locka);
	b = pthread_mutex_unlock(&lockb);
	
	printf("%s%d%s%d\n", "Child lock a: ", a, " unlock b: ", b);
	
}

long parent(){
	printf("parent locka = %x\n", &locka);
	int b = pthread_mutex_lock(&lockb);
	printf("parent before lock mutex A\n");
	int a = pthread_mutex_lock(&locka);
	printf("parent locked mutex A\n");
	pause();
	printf("%s%d%s%d\n", "Parent lock b: ", b, " unlock a: ", b);
	
	b = pthread_mutex_lock(&lockb);
	a = pthread_mutex_unlock(&locka);
	
	printf("%s%d%s%d\n", "Parent lock b: ", b, " unlock a: ", b);
	
	return 1;
}

void test_multiThreadStart() {
	assertTrue("Should return 1", 1 == multiThreadStart(&parent, &child));
}


int main(int argc, char **argv) {
	int a = pthread_mutex_init(&locka, NULL);
	int b = pthread_mutex_init(&lockb, NULL);
	
	printf("%s%d%s%d\n", "!!!!!!!!!!!!!------------------->>>>Init mut a: ", a, " init b: ", b);
	
	testSuit("Multi thread handler suit", 1, 
		initTestCase("Should sync", &test_multiThreadStart)		
	);
    return 0;
}
