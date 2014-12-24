#include "Key.h"
#include "Collection.h"

char getMessageStatus(char* message);

void getPrimaryKey(Key* key, char* message);

void getSecondKey(Key* key, char* message);

char handleMessage(char* message);

void initCollection(Collection* _collection);
