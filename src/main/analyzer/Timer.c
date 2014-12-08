#include <time.h>
#include "Configuration.h"

#define BILLON 1000000000

unsigned long getULongNano() {
	struct timespec currentTime;	
	clock_gettime(TIMER_ABSTIME, &currentTime);

	return (unsigned long) currentTime.tv_nsec;
}

unsigned int getUIntNano() {
	return (unsigned int) getULongNano();
}

unsigned char getUCharNano() {
	return (unsigned char) getULongNano();
}

unsigned long calcOffsetULong(unsigned long start){
	unsigned long end = getULongNano();
	return start < end ? end - start: end + BILLON - start;
}
