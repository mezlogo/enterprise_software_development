#include "Key.h"

#ifndef KEY_HANDLER_H
#define KEY_HANDLER_H

char compareKeys(Key* key1, Key* key2);

unsigned int hashCode(Key* key);

void keyToCharArray(Key* key, char* array);

void charArrayToKey(Key* key, char* array);
#endif
