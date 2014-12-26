#include "Random.h"
#include "Configuration.h"

//Блоки выделяются любого размера в пределах от 16 байт до 16Кбайт случайным образом при каждом выделении
int getRange() {
	return generateIntByRange(MIN_RANGE, MAX_RANGE);
}

int fixSizes[] = FIX_SIZES
//Блоки выделяются одного из перечисленных размеров случайным образом при каждом выделении: 16 байт, 64 байта, 256 байт, 1 Кбайт, 4 КБайта, 16 Кбайт.
int getFix() {
	return fixSizes[generateIntByWidth(
						FIX_SIZES_LENGTH)];
}
