#include "Key.h"
#include "KeyHandler.h"
#include "Random.h"

char isUniq(Key* key, Key* keys, int length) {
	while (0 < --length)
		if (0 == compareKeys(key, &keys[length]))
		{ return 1; }

	return 0;
}

void generateKey(Key* key) {
	key->ip = generateInt();
	key->port = generateShort();
}

void generateUniqKey(Key* key, Key* keys,
					 int length) {

	Key bufferKey;

	do {
		generateKey(&bufferKey);
	} while (1 == isUniq(&bufferKey, keys, length));

	key->port = bufferKey.port;
	key->ip = bufferKey.ip;
}

void generateUniqKeys(Key* keys, int length) {
	generateKey(&keys[0]);

	int count = 0;

	while (++count < length) {
		generateUniqKey(&keys[count], keys, count);
	}
}
