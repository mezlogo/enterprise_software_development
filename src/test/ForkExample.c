#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
#include <stdio.h>     /* printf, perror */
#include <stdlib.h>    /* exit */
#include <unistd.h>    /* _exit, fork */

int main(void) {
	pid_t pid = fork();

	if (pid == -1) {
		// When fork() returns -1, an error happened.
		perror("fork failed");
		exit(EXIT_FAILURE);

	} else if (pid == 0) {
		// When fork() returns 0, we are in the child process.
		printf("Hello from the child process!\n");
		_exit(EXIT_SUCCESS);  // exit() is unreliable here, so _exit must be used

	} else {
		printf("%s", "Parent!\n");
		sleep(1);
		printf("%s", "Parent!\n");
		// When fork() returns a positive number, we are in the parent process
		// and the return value is the PID of the newly created child process.
		int status;
		(void)waitpid(pid, &status, 0);
	}

	return EXIT_SUCCESS;
}
