#include <stdio.h>
#include <stdlib.h>
#include "minunit.h"
#include "ArrayHandler.h"

#include <inttypes.h>
#include "nanotime.h"

int tests_run = 0;

static char * test_findFirstZero() {
	int length = 4;
	char array[5] = {0, 1, 0, 1, 0}; 
	
    mu_assert("Should find zero index", findFirstZero(array, length) == 0);

	array[0] = 1;

	mu_assert("Should find second index", findFirstZero(array, length) == 2);
	
	array[2] = 1;
	
	mu_assert("Shouldn't find 0", findFirstZero(array, length) == -1);

	mu_assert("Should find 5 elem as 0, from 5 length array", findFirstZero(array, length + 1) == 4);

	struct nanotime now = nanotime_utc_now();

	printf("%" PRIu64 "\n", now.ns);

    return 0;
}

static char * all_tests() {
    mu_run_test(test_findFirstZero);

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
