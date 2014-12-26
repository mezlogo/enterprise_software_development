#include <stdio.h>
#include "Random.h"
#include "SimpleCUnit.h"

void test_generateCharShort() {
	assertTrue("Short shouldn't equalse",
			   generateShort() != generateShort());
	assertTrue("Char shouldn't equalse",
			   generateChar() != generateChar());
}

void test_generateIntByWidth() {
	int count = 100000;

	unsigned int value;

	int width = 100;

	while (count--) {
		value = generateIntByWidth(width);
		assertTrue("Value is out if width", 0 <= value &&
				   value < width);
	}

	assertTrue("If width eq 0, should return 0",
			   0 == generateIntByWidth(0));
	assertTrue("If width eq 1, should return 0",
			   0 == generateIntByWidth(1));
}

void test_generateIntByRange() {
	int count = 100000;

	unsigned int value;

	int start = 100;
	int end = 1000;

	while (count--) {
		value = generateIntByRange(start, end);
		assertTrue("Value is out of range",
				   start <= value && value < end);
	}

	assertTrue("Range should swap params, if end < start",
			   99 == generateIntByRange(100, 99));
}

int main(int argc, char** argv) {
	testSuit("Random suit", 3,
			 initTestCase("Generate by width",
						  &test_generateIntByWidth),
			 initTestCase("Generate primitives",
						  &test_generateCharShort),
			 initTestCase("Generate by range",
						  &test_generateIntByRange));
	return 0;
}
