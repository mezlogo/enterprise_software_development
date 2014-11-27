#include <stdio.h>
#include "ErrorCode.h"
#include "minunit.h"
#include "Subheap.h"
#include "MemoryManagerDevelop.h"

int tests_run = 0;


static char * test_init() {
	char subheapsCount = 4;
	int variablesSize[4] = {1, 2, 3, 4};
	int variablesCount[4] = {1, 1, 1, 1};
	
	mu_assert("Should first time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	mu_assert("Shouldn't init cos' subheap count -1", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, -1));
	mu_assert("Shouldn't init cos' subheap count 0", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, 0));
	mu_assert("Shouldn't init cos' subheap count 100000", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, 100000));
	
	mu_assert("Should second time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	variablesSize[2] = 1;
	mu_assert("Shouldn't init cos' variablesSize[2] = 1, isn't ascending", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, subheapsCount));
	
	variablesSize[2] = 3;
	mu_assert("Should third time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	variablesSize[0] = -21;
	mu_assert("Shouldn't init cos' variablesSize[0] = -1, isn't only positive", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, subheapsCount));
	
	variablesSize[0] = 1;
	mu_assert("Should four time init correctly", 0 == init(variablesSize, variablesCount, subheapsCount));
	variablesCount[0] = -1;
	mu_assert("Shouldn't init cos' variablesCount[0] = -1, isn't only positive", INITIAL_INPUT_PARAMS_ERROR == init(variablesSize, variablesCount, subheapsCount));
	
	
	return 0;
}

static char * test_allocate() {
	mu_assert("Should return NULL, cos' allocate -2", allocate(-2) == NULL);
	
	mu_assert("Should return NULL, cos' allocate 0", allocate(0) == NULL);
	
	mu_assert("Should return NULL, cos' allocate 276447232", allocate(276447232) == NULL);
	
	return 0;
}

static char * test_remove() {
	return 0;
}

static char * all_tests() {
    mu_run_test(test_init);
	mu_run_test(test_allocate);
	mu_run_test(test_remove);

    return 0;
}

int main(int argc, char **argv) {
    char *result = all_tests();

    if (result != 0) {
        printf("%s\n", result);
    } else {
        printf("ALL TESTS PASSED\n");
    }

    printf("Tests run: %d\n", tests_run);

    return result != 0;
}
