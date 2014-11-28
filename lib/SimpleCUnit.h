#include <stdio.h>
#include <stdarg.h>

//Colors
#define KNRM  "\x1B[0m"
#define KRED  "\x1B[31m"
#define KGRN  "\x1B[32m"
#define KYEL  "\x1B[33m"
#define KBLU  "\x1B[34m"
#define KMAG  "\x1B[35m"
#define KCYN  "\x1B[36m"
#define KWHT  "\x1B[37m"

#define TEST_FAIL -1
#define TEST_NOT_FAIL 0

#define assertTrue(message, test) isTestPass = TEST_NOT_FAIL; if (!(test)) {fileName = __FILE__; failFuncName = __func__; lineNumber = __LINE__; isTestPass = TEST_FAIL; errorMsg = message; return;} 

char* successMsg = "PASS";
char* failMsg = "FAIL";

const char* failFuncName;
char* fileName;
char* errorMsg = "No errors";
char errorCount = 0;
char lineNumber;
char isTestPass = TEST_NOT_FAIL;

typedef struct TestCase{
	char* testName;
	void (*testMethodPointer)();
} TestCase;

TestCase initTestCase(char* testName, void (*testMethodPointer)()){
	TestCase result = {testName, testMethodPointer};
	return result;
}

void runTestCase(TestCase testCase, char testNumber){
	testCase.testMethodPointer();
	
	printf("%-6d|%-30s|%-10s\n", testNumber, testCase.testName, isTestPass == TEST_FAIL ? failMsg : successMsg); 
    
	if(isTestPass == TEST_FAIL) printf("Error #%d in %s(%s:%d): %s%s%s.\n", ++errorCount, failFuncName, fileName, lineNumber, KMAG, errorMsg, KNRM);
}

void testSuit(char* testSuitName, int testCount, ...){
    va_list valist;
    int index = 0;
	errorCount = 0;
    /* initialize valist for num number of arguments */
    va_start(valist, testCount);
	printf("%s%s%s\n", KRED, "-------------------------------------------------------------", KNRM);
	printf("Start test suit: %s%s%s contain %s%d%s test cases.\n", KGRN, testSuitName, KNRM, KGRN, testCount, KNRM);
	printf("%-6s|%-30s|%-10s\n", "Num.", "Test case name", "Status"); 
    /* access all the arguments assigned to valist */
    for (; index < testCount; index++)
		runTestCase(va_arg(valist, TestCase), index + 1);
	
	printf("End of %s%s%s", KGRN, testSuitName, KNRM);
	
	if (0 < errorCount)
		printf(". Contain %s%d%s errors.\n", KRED, errorCount, KNRM);
	else
		printf(". %s%s%s", KYEL, "ALL TEST PASS!!!\n", KNRM);
	
    /* clean memory reserved for valist */
    va_end(valist);
}


