#include "Configuration.h"
#include "CyclicList.h"
#include "SimpleCUnit.h"

void test_case() {
    char some[1];
    char other[2];
    put(some);
    put(other);
    put(&other[1]);
    assertPointerEquals("Should put and next correctly", some, next());
    assertPointerEquals("Should put and next correctly", other, next());
    assertPointerEquals("Should put and next correctly", &other[1], next());
    assertPointerEquals("Should next eq NULL", NULL, next());

    char someOther[3];
    put(some);
    put(someOther);
    assertPointerEquals("Should next eq someOther", someOther, next());

    long index = 100000;

    char another[2];

    while (index--) {
	put(another);
	assertPointerEquals("Should next eq another", another, next());
    }
}

int main(int argc, char** argv) {
    testSuit("Cyclic list suit", 1,
	     initTestCase("Cyclic case", &test_case)
	    );
    return 0;
}
