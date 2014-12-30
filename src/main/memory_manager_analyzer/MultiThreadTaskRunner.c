#include "Configuration.h"
#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>


typedef pthread_mutex_t Mutex;

Mutex locka;
Mutex lockb;

void initMutex(Mutex* mutex) {
	int result = pthread_mutex_init(mutex, NULL);

	if (0 != result) { printf("%s%d\n", "Mutex init error: ", result); }
}

void unlockMutex(Mutex* mutex) {
	int result = pthread_mutex_unlock(mutex);

	if (0 != result) { printf("%s%d\n", "Mutex unlock error: ", result); }
}

void lockMutex(Mutex* mutex) {
	int result = pthread_mutex_lock(mutex);

	if (0 != result) { printf("%s%d\n", "Mutex lock error: ", result); }
}

void initThread(pthread_t* thread,
				void* (*method)()) {
	int err = pthread_create(thread, NULL, method,
							 NULL);

	if (err != 0)	{ printf("%s[%s]\n", "Can't create thread: ", strerror(err)); }
}

int (*mainAction)();
void (*additionalAction)();

long seesionCount;
long iterationCount;

void (*preIterationAction)();
void (*postIterationAction)();

char isCrash = NO_CRASH;

void threadTaskA() {

	while (CRASH != isCrash && seesionCount--) {

		preIterationAction();

		long index = iterationCount;

		while (CRASH != isCrash && index--) {
			lockMutex(&lockb);
			isCrash = mainAction();
			unlockMutex(&locka);
		}

		postIterationAction();
	}
}

void threadTaskB() {
	while (CRASH != isCrash ) {
		lockMutex(&locka);
		additionalAction();
		unlockMutex(&lockb);
	}
}

void tasksRun(int (*_mainAction)(),
			  void (*_additionalAction)(),
			  void (*_preIterationAction)(),
			  void (*_postIterationAction)(),
			  long _seesionCount, long _iterationCount) {
	mainAction = _mainAction;
	additionalAction = _additionalAction;

	preIterationAction = _preIterationAction;
	postIterationAction = _postIterationAction;

	seesionCount = _seesionCount;
	iterationCount = _iterationCount;

	//if variable isCrash contain value CRASH, that's bad.
	isCrash = NO_CRASH;

	initMutex(&locka);
	initMutex(&lockb);

	lockMutex(&locka);

	pthread_t threadA;
	pthread_t threadB;

	initThread(&threadA, (void*) &threadTaskA);
	initThread(&threadB, (void*) &threadTaskB);

	pthread_join(threadA, NULL);
	pthread_join(threadB, NULL);
}
