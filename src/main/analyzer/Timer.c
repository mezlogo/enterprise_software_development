#include <unistd.h>
#include <sys/types.h>
#include <errno.h>
#include <stdio.h>
#include <sys/wait.h>
#include <stdlib.h>

long multiThreadStart(long (*parent)(), void (*child)()){
	pid_t pid = fork();
	
	switch(pid) {
		case -1: //Error create child
			printf("%s", "Error exit, child can't create!\n");
			exit(1);         
			break;
		case 0: //Child
			child();
			exit(0);
			break;
		default: //Parent
			return parent();
	}
}
