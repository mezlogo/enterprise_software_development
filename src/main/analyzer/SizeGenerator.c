#include "Random.h"

#define MIN_RANGE 16
#define MAX_RANGE 16384
 
//Блоки выделяются любого размера в пределах от 16 байт до 16Кбайт случайным образом при каждом выделении
int getRange(){
	return generateIntByRange(MIN_RANGE, MAX_RANGE);
}

int fixSizes[] = {16, 64, 256, 1024, 4 * 1024, 16 * 1024};
//Блоки выделяются одного из перечисленных размеров случайным образом при каждом выделении: 16 байт, 64 байта, 256 байт, 1 Кбайт, 4 КБайта, 16 Кбайт.
int getFix(){
	return fixSizes[generateIntByWidth(6)];
}
