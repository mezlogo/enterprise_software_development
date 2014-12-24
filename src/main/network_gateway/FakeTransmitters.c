#include "Configuration.h"
#include "Key.h"
#include "Random.h"
#include "KeyGenerator.h"
#include "KeyHandler.h"

Key staticTransmitters[TRANSMITTERS_COUNT];
Key* transmitters = staticTransmitters;
unsigned int size = TRANSMITTERS_COUNT;

void setTransmitters(Key* newTransmitters, unsigned int newSize) {
    transmitters = newTransmitters;
    size = newSize;
}

/* Сгенерировать сообщение (на клиенте)
 * 1) установить тип сообщения, как обычное (измерить время поиска)
 * 2) получить случайный передатчик
 * 3) установить данные передатчика в сообщение
 * 4) если входной параметр (итерация) 50-ая, то изменить данные передатчика
 *		и записать измененые данные в сообщение
 * */
void generateMessage(char* message, unsigned long value) {
    message[0] = MESSAGE_TYPE_REGULAR;

    Key* currentKey = &transmitters[generateIntByWidth(size)];

    keyToCharArray(currentKey, &message[1]);

    if (0 == value % TRANSMITTER_ALTER_THRESHOLD_VALUE) {
	message[0] = MESSAGE_TYPE_ALTER;
	generateUniqKey(currentKey, transmitters, size);
	keyToCharArray(currentKey, &message[7]);
    }
}

void initTransmitters() {
    generateUniqKeys(transmitters, size);
}
