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

Key staticKey;

void generateUniqKey(Key* key, Key* keys, int length) {
    do {
	generateKey(&staticKey);
    } while (1 == isUniq(&staticKey, keys, length));

    key->port = staticKey.port;
    key->ip = staticKey.ip;
}

void generateUniqKeys(Key* keys, int length) {
    generateKey(&keys[0]);

    int count = 0;

    while (++count < length) {
	generateUniqKey(&keys[count], keys, count);
    }
}
