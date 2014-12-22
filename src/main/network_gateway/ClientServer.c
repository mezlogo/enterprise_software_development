#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#include "Key.h"

void error(const char* msg) {
    perror(msg);
    exit(1);
}

/////////////////////////////
/////////SERVER//////////////
/////////////////////////////

#define MESSAGE_TYPE_BYTE_COUNT 1
int maxMessageSize = 13;

int serverSocket;
int serverConnectClientSocket;

char startServer(unsigned int port) {
    maxMessageSize = MESSAGE_TYPE_BYTE_COUNT + 2 * sizeof(Key);

    socklen_t clilen;
    struct sockaddr_in serv_addr, cli_addr;


    serverSocket = socket(AF_INET, SOCK_STREAM, 0);
    if (serverSocket < 0)
    { error("ERROR opening socket"); }

    /*
     * turn off bind address checking, and allow
     * port numbers to be reused - otherwise
     * the TIME_WAIT phenomenon will prevent
     * binding to these address.port combinations
     * for (2 * MSL) seconds.
     */

    int on = 1;

    int status = setsockopt(serverSocket, SOL_SOCKET,
			    SO_REUSEADDR,
			    (const char*) &on, sizeof(on));

    if (-1 == status)
    { perror("setsockopt(...,SO_REUSEADDR,...)"); }

    bzero((char*) &serv_addr, sizeof(serv_addr));

    serv_addr.sin_family = AF_INET;
    serv_addr.sin_addr.s_addr = INADDR_ANY;
    serv_addr.sin_port = htons(port);

    if (bind(serverSocket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    { error("ERROR on binding"); }


    listen(serverSocket, 1);

    clilen = sizeof(cli_addr);

    serverConnectClientSocket = accept(serverSocket,
				       (struct sockaddr*) &cli_addr,
				       &clilen);

    if (serverConnectClientSocket < 0)
    { error("ERROR on accept"); }

    return 0;
}

void readMessage(char* message) {
    bzero(message, maxMessageSize);
    int readStatus = read(serverConnectClientSocket, message, maxMessageSize);

    if (readStatus < 0)
    { error("ERROR reading from socket"); }
}

void closeServer() {
    close(serverConnectClientSocket);
    close(serverSocket);
}

/////////////////////////////
/////////CLIENT//////////////
/////////////////////////////

#define LOCALHOST "localhost"

int clientSocket;

char startClient(unsigned int port) {
    struct sockaddr_in serv_addr;
    struct hostent* server;

    clientSocket = socket(AF_INET, SOCK_STREAM, 0);

    if (clientSocket < 0)
    { error("ERROR opening socket"); }

    server = gethostbyname(LOCALHOST);

    if (server == NULL) {
	fprintf(stderr, "ERROR, no such host\n");
	exit(0);
    }

    bzero((char*) &serv_addr, sizeof(serv_addr));
    serv_addr.sin_family = AF_INET;

    bcopy((char*)server->h_addr,
	  (char*)&serv_addr.sin_addr.s_addr,
	  server->h_length);

    serv_addr.sin_port = htons(port);

    if (connect(clientSocket, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    { error("ERROR connecting"); }

    return 0;
}



void sendMessage(char* message) {
    int sendStatus = write(clientSocket, message, maxMessageSize);

    if (sendStatus < 0)
    { error("ERROR writing to socket"); }
}

void closeClient() {
    close(clientSocket);
}
