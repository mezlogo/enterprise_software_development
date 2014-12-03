#include <time.h>

struct timespec currentTime;	
	
unsigned long getULongNano() {
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
	return getULongNano() - start;
}

unsigned int calcOffsetUInt(unsigned int start){
	return getUIntNano() - start;
}
