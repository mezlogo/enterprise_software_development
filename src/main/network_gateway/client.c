#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>
#include <string.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <netdb.h>

#define PORT_N 2000
#define LOCALHOST "localhost"

void error(const char* msg) {
    perror(msg);
    exit(0);
}


void clientStart() {
    int sockfd, portno, n;
    struct sockaddr_in serv_addr;
    struct hostent* server;

    char* msg = "Lol";

    portno = PORT_N;
    sockfd = socket(AF_INET, SOCK_STREAM, 0);

    if (sockfd < 0)
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
    serv_addr.sin_port = htons(portno);

    if (connect(sockfd, (struct sockaddr*) &serv_addr, sizeof(serv_addr)) < 0)
    { error("ERROR connecting"); }

    printf("Please enter the message: ");

    char buffer[256];
    bzero(buffer, 256);
    fgets(buffer, 255, stdin);

    n = write(sockfd, buffer, strlen(buffer));

    if (n < 0)
    { error("ERROR writing to socket"); }

    bzero(buffer, 256);

    n = read(sockfd, buffer, 255);

    if (n < 0)
    { error("ERROR reading from socket"); }
    printf("%s%s\n", "Return msg: ", buffer);
    close(sockfd);
}

int main(int argc, char* argv[]) {
    clientStart();
    return 0;
}
