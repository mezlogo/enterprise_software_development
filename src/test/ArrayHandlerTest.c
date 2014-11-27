#include <stdio.h>
#include <stdlib.h>
#include "ErrorCode.h"
#include "minunit.h"
#include "ArrayHandler.h"


int tests_run = 0;

static char * test_findFirstZero() {
	int length = 4;
	char array[5] = {0, 1, 0, 1, 0}; 
	
    mu_assert("Should find zero index", findFirstZero(array, length) == 0);

	array[0] = 1;

	mu_assert("Should find second index", findFirstZero(array, length) == 2);
	
	array[2] = 1;
	
	mu_assert("Shouldn't find 0", findFirstZero(array, length) == ZERO_NOT_FOUND);

	mu_assert("Should find 5 elem as 0, from 5 length array", findFirstZero(array, length + 1) == 4);
	
	return 0;
}

static char * test_resetAllChars() {
	int length = 5;
	char array[5] = {1, 1, 1, 1, 1}; 
	
	resetAllChars(array, length);
	
    mu_assert("Should be 0 at 0", array[0] == 0);
    mu_assert("Should be 0 at 1", array[1] == 0);
    mu_assert("Should be 0 at 2", array[2] == 0);
    mu_assert("Should be 0 at 3", array[3] == 0);
    mu_assert("Should be 0 at 4", array[4] == 0);

	return 0;
}

static char * test_sumOfMulOfTwoArray() {
	int length = 5;
	int first[5] = {1 ,2 ,3 ,4 ,5};
	int second[5] = {1 ,2 ,3 ,4 ,5};
	
	mu_assert("Sum of mul {1 ,2 ,3 ,4 ,5} * {1 ,2 ,3 ,4 ,5} should be 55", sumOfMulOfTwoArray(first, second, length) == 55);

	first[3] = 0;

	mu_assert("Sum of mul {1 ,2 ,3 ,0} * {1 ,2 ,3 ,4} should be 14", sumOfMulOfTwoArray(first, second, length - 1) == 14);

	return 0;
}

static char * test_sumOfArray() {
	int length = 5;
	int array[5] = {1 ,2 ,3 ,4 ,5};
	
	mu_assert("Sum of {1 ,2 ,3 ,4 ,5} should be 15", sumOfArray(array, length) == 15);

	return 0;
}


static char * test_isAscending() {
	int length = 5;
	int array[5] = {1 ,2 ,3 ,4 ,5};
	
	mu_assert("{1 ,2 ,3 ,4 ,5} should be ascending", isAscending(array, length) == ONLY_ACSENDING);
	
	mu_assert("{1} should be ascending", isAscending(array, 1) == ONLY_ACSENDING);

	array[1] = 0;

	mu_assert("{1 ,0 ,3 ,4 ,5} shouldn't ascending and return 1 as index of invalid element", isAscending(array, length) == 1);

	return 0;
}

static char * test_isOnlyPositive() {
	int length = 5;
	int array[5] = {1 ,2 ,3 ,4 ,5};
	
	mu_assert("{1 ,2 ,3 ,4 ,5} should be positive", isOnlyPositive(array, length) == ONLY_POSITIVES);
	
	array[3] = -23;

	mu_assert("{1 ,2 ,3 ,-23 ,5} shouldn't positive and return 3 as index of invalid element", isOnlyPositive(array, length) == 3);

	return 0;
}

static char * all_tests() {
    mu_run_test(test_findFirstZero);
	mu_run_test(test_resetAllChars);
	mu_run_test(test_sumOfMulOfTwoArray);
	mu_run_test(test_sumOfArray);
	mu_run_test(test_isAscending);
	mu_run_test(test_isOnlyPositive);
	
    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();

    if (result != 0) {
        printf("!!!!!!|%s|!!!!!!\n", result);
    } else {
        printf("<----------ALL TESTS PASSED---------->\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
