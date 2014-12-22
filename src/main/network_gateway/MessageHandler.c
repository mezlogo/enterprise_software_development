#include "Key.h"
#include "KeyHandler.h"

char getMessageStatus(char * message) {
	return *message;
}

void getPrimaryKey(Key * key, char * message) {
	charArrayToKey(key, &message[1]);
}

void getSecondKey(Key * key, char * message) {
	charArrayToKey(key, &message[7]);
}



