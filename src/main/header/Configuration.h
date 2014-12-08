#ifndef ERROR_CODE_H
#define ERROR_CODE_H

//////////////////
//Memory manager//
//////////////////

//Configuration//
#define MAX_HEAP_SIZE 10485760
#define MAX_HEAPS_COUNT 15
#define MAX_VARIABLES_COUNT 100000

//Result//

//Success
#define ONLY_POSITIVES -1
#define ONLY_ACSENDING -1
#define VARIABLE_REMOVE_SUCCESS 0
#define INITIAL_SUCCESS 0


//Fail
#define ZERO_NOT_FOUND -1
#define INITIAL_INPUT_PARAMS_ERROR -1
#define INITIAL_ERROR_MANAGER_TOO_SMALL -2
#define VARIABLE_REMOVE_FAIL -1



////////////
//Analyzer//
////////////

//Configuration//
#define ITERATION_COUNT 100000
#define SESSION_COUNT 5

#define MIN_RANGE 16
#define MAX_RANGE 16384

#define NO_CRASH 1
#define CRASH 0

#define REMOVE_MAX_CHANCE 1000
#define REMOVE_CHANCE 500

#define FIX_SIZES_LENGTH 6
#define FIX_SIZES {16, 64, 256, 1024, 4 * 1024, 16 * 1024};

#define ANALYZE_VARIABLES_SIZE {2, 4, 8, 16};
#define ANALYZE_VARIABLES_COUNT {10, 10, 10, 10};
#define ANALYZE_SUBHEAPS_COUNT 4



#endif /*ERROR_CODE_H*/
