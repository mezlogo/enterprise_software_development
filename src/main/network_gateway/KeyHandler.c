#include "Key.h"

void keyToCharArray(Key* key, char* array) {
    unsigned int* ip = (unsigned int*) array;
    unsigned short* port = (unsigned short*) &array[4];
    *ip = key->ip;
    *port = key->port;
}

char compareKeys(Key* key1, Key* key2) {
    //Compare ip: if key1.ip less that key2.ip than -1 etc
    char result = (key1->ip < key2->ip ? -1 : (key1->ip == key2->ip ? 0 : 1) );
    //Compare port, only if ips eq
    result = (0 == result ? (key1->port < key2->port ? -1 : key1->port == key2->port ? 0 : 1) : result);

    return result;
}

unsigned int hashCode(Key* key) {
    return key->ip;
}
