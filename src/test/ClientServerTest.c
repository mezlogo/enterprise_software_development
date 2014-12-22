#include <sys/types.h> /* pid_t */
#include <sys/wait.h>  /* waitpid */
//#include <stdio.h>     /* printf, perror */
#include <stdlib.h>    /* exit */
#include <unistd.h>    /* _exit, fork */

#include <stdio.h>
#include "ClientServer.h"
#include "SimpleCUnit.h"

void test_case() {
    int status;
    pid_t pid = fork();

    switch (pid) {
    case -1: //Error
	exit(EXIT_FAILURE);
	break;

    case 0: //Child
	startClient(2000);
	sendMessage("Sipport00000a0");
	sendMessage("sipPORT658432");
	sendMessage("Sipport s");
	sendMessage("Sipportasas651651");
	_exit(EXIT_SUCCESS);
	break;

    default: //Parent
	startServer(2000);
	char message[20];

	readMessage(message);
	printf("Here is the message: %s\n", message);

	readMessage(message);
	printf("Here is the message: %s\n", message);

	readMessage(message);
	printf("Here is the message: %s\n", message);

	readMessage(message);
	printf("Here is the message: %s\n", message);

	(void) waitpid(pid, &status, 0);
	break;
    }

    closeClient();
    closeServer();
}

int main(int argc, char** argv) {
    testSuit("Client server suit", 1,
	     initTestCase("Main case", &test_case));
    return 0;
}
