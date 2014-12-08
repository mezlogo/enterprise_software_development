#include "Configuration.h"
#include "TaskRunner.h"
#include "SimpleCUnit.h"

typedef pthread_mutex_t Mutex;

Mutex locka;
Mutex lockb;

void initMutex(Mutex * mutex) {
	int result = pthread_mutex_init(mutex, NULL);
	if (0 != result) printf("%s%d\n", "Mutex init error: ", result);
}

void unlockMutex(Mutex * mutex) {
	int result = pthread_mutex_unlock(mutex);
	if (0 != result) printf("%s%d\n", "Mutex unlock error: ", result);
}

void lockMutex(Mutex * mutex) {
	int result = pthread_mutex_lock(mutex);
	if (0 != result) printf("%s%d\n", "Mutex lock error: ", result);
}

void child(){
	sleep(1);
	printf("Child init\n");
	
	unlockMutex(&locka);
	lockMutex(&lockb);
	
	printf("Child 1\n");
	
	unlockMutex(&lockb);
	lockMutex(&locka);
	
	unlockMutex(&locka);
	lockMutex(&lockb);
	
	printf("Child 2\n");
	
	unlockMutex(&lockb);
	lockMutex(&locka);
}

void parent(){	
	printf("Parent init\n");

	unlockMutex(&lockb);
/*	lockMutex(&locka);
	
	printf("Parent 1\n");
	
	unlockMutex(&locka);
	lockMutex(&lockb);
	
	unlockMutex(&lockb);
	lockMutex(&locka);
	
	printf("Parent 2\n");
	
	unlockMutex(&locka);
	lockMutex(&lockb);*/
}

void test_multiThreadStart() {
	multiThreadStart(&parent, &child);
}

int main(int argc, char **argv) {
	initMutex(&locka);
	initMutex(&lockb);

	lockMutex(&locka);
	lockMutex(&lockb);
	
	testSuit("Multi thread handler suit", 1, 
		initTestCase("Should sync", &test_multiThreadStart)		
	);
    return 0;
}
