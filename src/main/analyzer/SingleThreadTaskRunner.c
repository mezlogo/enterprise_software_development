void tasksRun(int (*parent)(), void (*child)(), void (*preIteration)(), void (*postIteration)(), long seesionCount, long iterationCount) {
	
	//crash == 0
	char isCrash = 1;
	
	while (isCrash && seesionCount--) {
		
		preIteration();
		
		long index = iterationCount;
		
		while (isCrash && index--) {
			isCrash = parent();
			child();
		}
		
		postIteration();
	}
}
