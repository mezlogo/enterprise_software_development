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

#define assertTrue(message, test) assertationType = ASSERT_TYPE_TRUE; isTestPass = TEST_NOT_FAIL; if (!(test)) {fileName = __FILE__; failFuncName = __func__; lineNumber = __LINE__; isTestPass = TEST_FAIL; errorMsg = message; return;} 

#define assertLongEquals(message, expected, actual) assertationType = ASSERT_TYPE_LONG_EQUALS; isTestPass = TEST_NOT_FAIL; if ((actual) != (expected)) {fileName = __FILE__; failFuncName = __func__; lineNumber = __LINE__; isTestPass = TEST_FAIL; errorMsg = message; expectedValue = expected; actualValue = actual; return;} 

#define assertPointerEquals(message, expected, actual) assertationType = ASSERT_TYPE_POINTER_EQUALS; isTestPass = TEST_NOT_FAIL; if ((actual) != (expected)) {fileName = __FILE__; failFuncName = __func__; lineNumber = __LINE__; isTestPass = TEST_FAIL; errorMsg = message; expectedPointer = expected; actualPointer = actual; return;} 


char* successMsg = "PASS";
char* failMsg = "FAIL";

const char* failFuncName;
char* fileName;
char* errorMsg = "No errors";
char errorCount = 0;
char lineNumber;
char isTestPass = TEST_NOT_FAIL;


#define ASSERT_TYPE_TRUE 1
#define ASSERT_TYPE_LONG_EQUALS 2
#define ASSERT_TYPE_POINTER_EQUALS 3
char assertationType;
long expectedValue;
char * expectedPointer;
long actualValue;
char * actualPointer;

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
    
	if(isTestPass == TEST_FAIL) { 
		switch (assertationType) {
			case ASSERT_TYPE_TRUE: 
				printf("Error #%d in %s(%s:%d): %s%s%s.\n", ++errorCount, failFuncName, fileName, lineNumber, KRED, errorMsg, KNRM); 
				break;
			case ASSERT_TYPE_POINTER_EQUALS:
				printf("Error #%d in %s(%s:%d): %s%s%s. \n%s%p%s%p%s\n", ++errorCount, failFuncName, fileName, lineNumber, KRED, errorMsg, KYEL, "Expected: ", expectedPointer, " Actual: ", actualPointer, KNRM);
				break;
			case ASSERT_TYPE_LONG_EQUALS: 
				printf("Error #%d in %s(%s:%d): %s%s%s. \n%s%lu%s%lu%s\n", ++errorCount, failFuncName, fileName, lineNumber, KRED, errorMsg, KYEL, "Expected: ", expectedValue, " Actual: ", actualValue, KNRM); 
				break;
			default: 
				printf("%s", "Assert's type sn't defined!/n");
		}
		
	}
	// Fix: if test case had no assertation AND prev test case was failed, then current test case, seems like failed test case.
	isTestPass = TEST_NOT_FAIL;
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


