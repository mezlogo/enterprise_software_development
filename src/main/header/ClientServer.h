char startServer(unsigned int port);

char startClient(unsigned int port);

void closeServer();

void closeClient();

void sendMessage(char* message);

void readMessage(char* message);
