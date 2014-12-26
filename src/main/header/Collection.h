#include "Key.h"

#ifndef COLLECTION_H
#define COLLECTION_H

struct Collection {
	char (*find)(Key* key);
	char (*insert)(Key* key);
	char (*alter)(Key* source, Key* target);
};

typedef struct Collection Collection;

#endif
