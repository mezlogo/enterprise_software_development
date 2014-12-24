#ifndef CONFIGURATION_H
#define CONFIGURATION_H

//////////////////
//Memory manager//
//////////////////

//Configuration//
#define MAX_HEAP_SIZE 10485760
#define MAX_HEAPS_COUNT 15
#define MAX_VARIABLES_COUNT 50000

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
#define LOGGER_SIZE 1000000
#define ITERATION_COUNT 100000
#define SESSION_COUNT 5

#define MIN_RANGE 16
#define MAX_RANGE 16384

#define NO_CRASH 1
#define CRASH 0

#define REMOVE_MAX_CHANCE 1000
#define REMOVE_CHANCE 700

#define FIX_SIZES_LENGTH 6
#define FIX_SIZES {16, 64, 256, 1024, 4 * 1024, 16 * 1024};

#define ANALYZE_VARIABLES_SIZE {16, 64, 256, 1024, 4096, 16384}
#define ANALYZE_VARIABLES_COUNT {480, 480, 480, 480, 480, 480}
#define ANALYZE_SUBHEAPS_COUNT 6

///////////////////
//Network gateway//
///////////////////

//Configuration//
#define TRANSMITTERS_COUNT 10000
#define MESSAGE_SIZE 13

#define TRANSMITTER_ALTER_THRESHOLD_VALUE 50

#define MESSAGE_TYPE_REGULAR 1
#define MESSAGE_TYPE_ALTER 2

#define MESSAGE_VALID 0
#define MESSAGE_INVALID 1

//////////////////
//Collection//////
//////////////////

#define FIND_SUCCESS 0
#define FIND_FAIL 1

#define INSERT_SUCCESS 0
#define INSERT_FAIL 1

#define ALTER_SUCCESS 0
#define ALTER_FAIL 1
#define REMOVE_SUCCESS 2

#define LINKED_LIST_NODE_NOT_FOUND -1
#define LINKED_LIST_NODE_ROOT_IS_NULL -2
#define LINKED_LIST_NODE_ROOT_IS_CANT_BE_REMOVED -3
#define LINKED_LIST_NODE_SUCCESS_OP 0

#define HASH_TABLE_INIT_FAIL -1
#define HASH_TABLE_INIT_SUCCESS 0

#endif /*CONFIGURATION_H*/
