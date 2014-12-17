#include <stdio.h>
#include "LinkedList.h"
#include "Key.h"
#include "SimpleCUnit.h"

void test_case() {
    printf("%s%lu%s%lu\n", "\nKey: ", sizeof(Key), "\nList: ", sizeof(LinkedList));
    Key k1;

}

int main(int argc, char** argv) {
    testSuit("Linked list suit", 1,
	     initTestCase("Main case", &test_case));
    return 0;
}
