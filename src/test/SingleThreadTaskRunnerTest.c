#include "Configuration.h"
#include "TaskRunner.h"
#include "SimpleCUnit.h"

char isChildOk = 0; 
char isParentOk = 0; 
char isPreIterationOk = 1; 
char isPostIterationOk = 2; 
long totalIterationCouter = 0;


int parent() {
	totalIterationCouter++;
	return ++isParentOk < 8; 
}

void child() {
	if (0 == totalIterationCouter % 2)
		isChildOk++; 
}

void preIteration() {
	isPreIterationOk <<= 2; 
}

void postIteration() {
	isPostIterationOk <<= 1; 
}

void test_runner() {
	assertLongEquals("Pre parent condition", 0, isParentOk);
	assertLongEquals("Pre child condition", 0, isChildOk);
	assertLongEquals("Pre preIteration condition", 1, isPreIterationOk);
	assertLongEquals("Pre postIteration condition", 2, isPostIterationOk);
	assertLongEquals("Pre total itearation counter", 0, totalIterationCouter);
	
	tasksRun(&parent, &child, &preIteration, &postIteration, 2, 5);
	
	assertLongEquals("Post total itearation counter", 8, totalIterationCouter);
	assertLongEquals("Post parent condition", 8, isParentOk);
	assertLongEquals("Post child condition", 4, isChildOk);
	assertLongEquals("Post preIteration condition", 16, isPreIterationOk);
	assertLongEquals("Post postIteration condition", 8, isPostIterationOk);
}

int main(int argc, char **argv) {
	testSuit("Single thread task tunner suit", 1,	
		initTestCase("Runner case", &test_runner)		
	);
    return 0;
}
