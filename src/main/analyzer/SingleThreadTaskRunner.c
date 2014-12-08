#include "Configuration.h"

void tasksRun(int (*parent)(), void (*child)(), void (*preIteration)(), void (*postIteration)(), long seesionCount, long iterationCount) {
	
	//if isCrash == CRASH, that mean = crash
	char isCrash = NO_CRASH;
	
	while (CRASH != isCrash && seesionCount--) {
		
		preIteration();
		
		long index = iterationCount;
		
		while (CRASH != isCrash && index--) {
			isCrash = parent();
			child();
		}
		
		postIteration();
	}
}
