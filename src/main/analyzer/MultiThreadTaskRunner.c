#include <stdio.h>
#include <string.h>
#include <pthread.h>
#include <stdlib.h>
#include <unistd.h>

void tasksRun(void (*parent)(), void (*child)()){
	pthread_t tid;
	int err = pthread_create(&(tid), NULL, (void*) (*parent), NULL);
      
    if (err != 0)	printf("%s[%s]\n", "Can't create thread: ", strerror(err));
	
	pthread_t tida;
	int erra = pthread_create(&(tida), NULL, (void*) (*child), NULL);
      
    if (erra != 0)	printf("%s[%s]\n", "Can't create thread: ", strerror(erra));
	
	
	pthread_join(tid, NULL);
	pthread_join(tida, NULL);
}
