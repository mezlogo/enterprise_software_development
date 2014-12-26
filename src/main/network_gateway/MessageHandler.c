#include <stdio.h>
#include "Key.h"
#include "KeyHandler.h"
#include "Configuration.h"
#include "Collection.h"
#include "Logger.h"
#include "Timer.h"

#include "DevLog.h"

Collection collection;

void initCollection(Collection* _collection) {
	collection = *_collection;
}

char getMessageStatus(char* message) {
	return *message;
}

void getPrimaryKey(Key* key, char* message) {
	charArrayToKey(key, &message[1]);
}

void getSecondKey(Key* key, char* message) {
	charArrayToKey(key, &message[7]);
}

char handleMessage(char* message) {
	char collectionStatus;
	unsigned long startTime;
	unsigned long measureTime;
	Key primaryKey;
	Key secondKey;

	getPrimaryKey(&primaryKey, message);

	switch (getMessageStatus(message)) {

	case MESSAGE_TYPE_REGULAR: {
			startTime			= getULongNano();
			collectionStatus	= collection.find(&primaryKey);
			measureTime			= calcOffsetULong(startTime);

			if (FIND_SUCCESS == collectionStatus)	{
				//kLog("Success find", &primaryKey);
				logPrimary(measureTime);

			} else {
				kLog("Unsuccess find", &primaryKey);
			}
		}
		break;

	case MESSAGE_TYPE_ALTER: {
			getSecondKey(&secondKey, message);

			startTime 			= getULongNano();
			collectionStatus 	= collection.alter(&primaryKey,
												   &secondKey);
			measureTime			= calcOffsetULong(startTime);

			if (ALTER_SUCCESS != collectionStatus) {
				dkLog("Unsuccess alter", &primaryKey, &secondKey);

			} else {
				//dkLog("Success alter", &primaryKey, &secondKey);
				logSecondary(measureTime);
			}
		}
		break;

	default:
		printf("%s", "Invalid message type\n");
		return MESSAGE_INVALID;
	}

	return MESSAGE_VALID;
}

