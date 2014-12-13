#include <stdio.h>
#include <stdlib.h>
#include "Configuration.h"
#include "SimpleCUnit.h"
#include "ArrayHandler.h"


void test_findFirstZero() {
    int length = 4;
    char array[5] = {0, 1, 0, 1, 0};

    assertTrue("Should find zero index", findFirstZero(array, length) == 0);

    array[0] = 1;

    assertTrue("Should find second index", findFirstZero(array, length) == 2);

    array[2] = 1;

    assertTrue("Shouldn't find 0", findFirstZero(array, length) == ZERO_NOT_FOUND);

    assertTrue("Should find 5 elem as 0, from 5 length array", findFirstZero(array, length + 1) == 4);
}

void test_resetAllChars() {
    int length = 5;
    char array[5] = {1, 1, 1, 1, 1};

    resetAllChars(array, length);

    assertTrue("Should be 0 at 0", array[0] == 0);
    assertTrue("Should be 0 at 1", array[1] == 0);
    assertTrue("Should be 0 at 2", array[2] == 0);
    assertTrue("Should be 0 at 3", array[3] == 0);
    assertTrue("Should be 0 at 4", array[4] == 0);
}

void test_sumOfMulOfTwoArray() {
    int length = 5;
    int first[5] = {1 , 2 , 3 , 4 , 5};
    int second[5] = {1 , 2 , 3 , 4 , 5};

    assertTrue("Sum of mul {1 ,2 ,3 ,4 ,5} * {1 ,2 ,3 ,4 ,5} should be 55", sumOfMulOfTwoArray(first, second, length) == 55);

    first[3] = 0;

    assertTrue("Sum of mul {1 ,2 ,3 ,0} * {1 ,2 ,3 ,4} should be 14", sumOfMulOfTwoArray(first, second, length - 1) == 14);
}

void test_sumOfArray() {
    int length = 5;
    int array[5] = {1 , 2 , 3 , 4 , 5};

    assertTrue("Sum of {1 ,2 ,3 ,4 ,5} should be 15", sumOfArray(array, length) == 15);
}

void test_isAscending() {
    int length = 5;
    int array[5] = {1 , 2 , 3 , 4 , 5};

    assertTrue("{1 ,2 ,3 ,4 ,5} should be ascending", isAscending(array, length) == ONLY_ACSENDING);

    assertTrue("{1} should be ascending", isAscending(array, 1) == ONLY_ACSENDING);

    array[1] = 0;

    assertTrue("{1 ,0 ,3 ,4 ,5} shouldn't ascending and return 1 as index of invalid element", isAscending(array, length) == 1);
}

void test_isOnlyPositive() {
    int length = 5;
    int array[5] = {1 , 2 , 3 , 4 , 5};

    assertTrue("{1 ,2 ,3 ,4 ,5} should be positive", isOnlyPositive(array, length) == ONLY_POSITIVES);

    array[3] = -23;

    assertTrue("{1 ,2 ,3 ,-23 ,5} shouldn't positive and return 3 as index of invalid element", isOnlyPositive(array, length) == 3);
}

int main(int argc, char** argv) {
    testSuit("Array handler test suit", 6,
	     initTestCase("Find first zero", &test_findFirstZero),
	     initTestCase("Reset all chars", &test_resetAllChars),
	     initTestCase("Sum of mul two array", &test_sumOfMulOfTwoArray),
	     initTestCase("Sum of array", &test_sumOfArray),
	     initTestCase("Is ascending", &test_isAscending),
	     initTestCase("Is only positive", &test_isOnlyPositive)
	    );
    return 0;
}
