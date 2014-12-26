#include <stdio.h>
#include "Key.h"

#ifndef DEV_H
#define DEV_H


void kLog(char* msg, Key* key) {
	printf("%s ip: %08x port %04x\n", msg, key->ip, key->port);
}

void dkLog(char* msg, Key* key1, Key* key2) {
	printf("%s ip: %08x port %04x AND ip: %08x port %04x\n", msg, key1->ip, key1->port, key2->ip,
		   key2->port);
}
#endif
