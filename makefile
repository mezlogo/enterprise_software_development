BUILD_DIR = build
SRC_DIR = src
MAIN_DIR = ${SRC_DIR}/main
TEST_DIR = ${SRC_DIR}/test
HEADERS_DIR = ${MAIN_DIR}/header

MEMORY_MANAGER_IMPLEMENT_DIR = ${MAIN_DIR}/memory_manager
ANALYZER_IMPLEMENT_DIR = ${MAIN_DIR}/analyzer
NETWORK_GATEWAY_DIR = ${MAIN_DIR}/network_gateway

TEST_FRMAWORK_DIR = lib

COMPILE = gcc
CFLAGS = -g -Wall
COMPILE_SOURCE = ${COMPILE} ${CFLAGS} -c
COMPILE_TEST = ${COMPILE} ${CFLAGS} -DEBUG
COMPILE_DEBUG = ${COMPILE} ${CFLAGS} -DEBUG -v -da -Q
MULTI_THREAD_COMPILE_FLAG = -lpthread

ARCHIVE = ar -crsv
RECURSIVE_REMOVE = rm -rf
CREATE_DIRS = mkdir

ARRAY_HANDLER_OBJECT = ${BUILD_DIR}/ArrayHandler.o
SUBHEAP_HANDLER_OBJECT = ${BUILD_DIR}/SubheapHandler.o
MEMORY_MANAGER_OBJECT = ${BUILD_DIR}/MemoryManager.o

RANDOM_OBJECT = ${BUILD_DIR}/Random.o
TIMER_OBJECT = ${BUILD_DIR}/Timer.o
SIZE_GENERATOR = ${BUILD_DIR}/SizeGenerator.o
SINGLE_THREAD_TASK_RUNNER = ${BUILD_DIR}/SingleThreadTaskRunner.o
CYCLIC_LIST_OBJECT = ${BUILD_DIR}/CyclicList.o
LOGGER_OBJECT = ${BUILD_DIR}/Logger.o
ANALYZER_API_OBJECT = ${BUILD_DIR}/AnalyzerAPI.o
MULTI_THREAD_TASK_RUNNER_OBJECT = ${BUILD_DIR}/MultiThreadTaskRunner.o

KEY_HANDLER_OBJECT = ${BUILD_DIR}/KeyHandler.o
KEY_GENERATOR_OBJECT = ${BUILD_DIR}/KeyGenerator.o
FAKE_TRANSMITTERS_OBJECT = ${BUILD_DIR}/FakeTransmitters.o
CLIENT_SERVER_OBJECT = ${BUILD_DIR}/ClientServer.o
MESSAGE_HANDLER_OBJECT = ${BUILD_DIR}/MessageHandler.o
NETWORK_GATEWAY_API_OBJECT = ${BUILD_DIR}/NetworkGatewayAPI.o

LINKED_LIST_HANDER_OBJECT = ${BUILD_DIR}/LinkedListHandler.o
AVL_NODE_HANDER_OBJECT = ${BUILD_DIR}/AVLNodeHandler.o
B_NODE_HANDER_OBJECT = ${BUILD_DIR}/BNodeHandler.o
AVL_TREE_OBJECT = ${BUILD_DIR}/AVLTree.o
B_TREE_OBJECT = ${BUILD_DIR}/BTree.o
HASH_TABLE_OBJECT = ${BUILD_DIR}/HashTable.o

START_MSG = @echo "<--------Start compile and testing"
END_MSG = @echo "<--------End compile and testing"

all: compile_and_test_logger

memory_manager_analyzer: compile_and_test_analyzer

network_gateway_api: compile_and_test_network_gateway_api

without_time: compile_and_test_memory_manager compile_and_test_cyclic_list compile_and_test_multi_thread_task_runner compile_and_test_logger compile_and_test_client_server  compile_and_test_hash_table compile_and_test_avl_tree compile_and_test_b_tree

integrate: compile_and_test_memory_manager compile_and_test_size_generator compile_and_test_cyclic_list compile_and_test_single_thread_task_runner compile_and_test_logger compile_and_test_analyzer compile_and_test_client_server compile_and_test_message_handler compile_and_test_b_tree

clean:
	${RECURSIVE_REMOVE} ${BUILD_DIR}
	#rm *.c.*

check: make_build_dir
	./cppcheck -q --enable=style,performance,warning -I${HEADERS_DIR} --template='{severity}\t{id} {file}:{line} {message}' ${MAIN_DIR} 2> ${BUILD_DIR}/suppress-log.txt
	
form:
	astyle -H -k1 -J  -xC100   -p -F -xW -T -K -A2 -r -n src/*.c src/*.h
#-O -W -m0 -M -xG -xL
make_build_dir: clean
	${CREATE_DIRS} ${BUILD_DIR}

########################Memory manager###################################

compile_and_test_array_handler: make_build_dir
	${START_MSG} array_handler
	${COMPILE_SOURCE} ${MEMORY_MANAGER_IMPLEMENT_DIR}/ArrayHandler.c -o ${ARRAY_HANDLER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libArrayHandler.a ${ARRAY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/ArrayHandlerTest.c -o ${BUILD_DIR}/ArrayHandlerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lArrayHandler -I${HEADERS_DIR}	
	./${BUILD_DIR}/ArrayHandlerTest
	${END_MSG} array_handler
	
compile_and_test_subheap_handler: make_build_dir
	${START_MSG} subheap_handler
	${COMPILE_SOURCE} ${MEMORY_MANAGER_IMPLEMENT_DIR}/SubheapHandler.c -o ${SUBHEAP_HANDLER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libSubheapHandler.a ${SUBHEAP_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/SubheapHandlerTest.c -o ${BUILD_DIR}/SubheapHandlerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lSubheapHandler -I${HEADERS_DIR}	
	./${BUILD_DIR}/SubheapHandlerTest
	${END_MSG} subheap_handler
	

compile_and_test_memory_manager: compile_and_test_array_handler compile_and_test_subheap_handler
	${START_MSG} memory_manager
	${COMPILE_SOURCE} ${MEMORY_MANAGER_IMPLEMENT_DIR}/MemoryManagerSubheapImpl.c -o ${MEMORY_MANAGER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libMemoryManager.a ${MEMORY_MANAGER_OBJECT} ${SUBHEAP_HANDLER_OBJECT} ${ARRAY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/MemoryManagerTest.c -o ${BUILD_DIR}/MemoryManagerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lMemoryManager -I${HEADERS_DIR}	
	./${BUILD_DIR}/MemoryManagerTest
	${END_MSG} memory_manager
	
########################Analyzer###################################
	
compile_and_test_multi_thread_task_runner: make_build_dir
	${START_MSG} multi_thread_task_runner
	${COMPILE_SOURCE} ${ANALYZER_IMPLEMENT_DIR}/MultiThreadTaskRunner.c -o ${MULTI_THREAD_TASK_RUNNER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libMultiThreadTaskRunner.a ${MULTI_THREAD_TASK_RUNNER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/MultiThreadTaskRunnerTest.c -o ${BUILD_DIR}/MultiThreadTaskRunnerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lMultiThreadTaskRunner -I${HEADERS_DIR} ${MULTI_THREAD_COMPILE_FLAG}
	./${BUILD_DIR}/MultiThreadTaskRunnerTest
	${END_MSG} multi_thread_task_runner

compile_and_test_single_thread_task_runner: make_build_dir
	${START_MSG} single_thread_task_runner
	${COMPILE_SOURCE} ${ANALYZER_IMPLEMENT_DIR}/SingleThreadTaskRunner.c -o ${SINGLE_THREAD_TASK_RUNNER} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libSingleThreadTaskRunner.a ${SINGLE_THREAD_TASK_RUNNER}
	${COMPILE_TEST} ${TEST_DIR}/SingleThreadTaskRunnerTest.c -o ${BUILD_DIR}/SingleThreadTaskRunnerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lSingleThreadTaskRunner -I${HEADERS_DIR}
	./${BUILD_DIR}/SingleThreadTaskRunnerTest
	${END_MSG} single_thread_task_runner
	
compile_and_test_timer: make_build_dir
	${START_MSG} timer
	${COMPILE_SOURCE} ${ANALYZER_IMPLEMENT_DIR}/Timer.c -o ${TIMER_OBJECT} -I${HEADERS_DIR} -lrt	
	${ARCHIVE} ${BUILD_DIR}/libTimer.a ${TIMER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/TimerTest.c -o ${BUILD_DIR}/TimerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lTimer -I${HEADERS_DIR}	
	./${BUILD_DIR}/TimerTest
	${END_MSG} timer
	
compile_and_test_random: compile_and_test_timer
	${START_MSG} random
	${COMPILE_SOURCE} ${ANALYZER_IMPLEMENT_DIR}/Random.c -o ${RANDOM_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libRandom.a ${RANDOM_OBJECT} ${TIMER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/RandomTest.c -o ${BUILD_DIR}/RandomTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lRandom -I${HEADERS_DIR}	
	./${BUILD_DIR}/RandomTest
	${END_MSG} random

compile_and_test_size_generator: compile_and_test_random
	${START_MSG} size_generator
	${COMPILE_SOURCE} ${ANALYZER_IMPLEMENT_DIR}/SizeGenerator.c -o ${SIZE_GENERATOR} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libSizeGenerator.a ${RANDOM_OBJECT} ${TIMER_OBJECT} ${SIZE_GENERATOR}
	${COMPILE_TEST} ${TEST_DIR}/SizeGeneratorTest.c -o ${BUILD_DIR}/SizeGeneratorTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lSizeGenerator -I${HEADERS_DIR}	
	./${BUILD_DIR}/SizeGeneratorTest
	${END_MSG} size_generator

compile_and_test_cyclic_list: make_build_dir
	${START_MSG} cyclic_list
	${COMPILE_SOURCE} ${ANALYZER_IMPLEMENT_DIR}/CyclicList.c -o ${CYCLIC_LIST_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libCyclicList.a ${CYCLIC_LIST_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/CyclicListTest.c -o ${BUILD_DIR}/CyclicListTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lCyclicList -I${HEADERS_DIR}	
	./${BUILD_DIR}/CyclicListTest
	${END_MSG} cyclic_list

compile_and_test_logger: make_build_dir
	${START_MSG} logger
	${COMPILE_SOURCE} ${ANALYZER_IMPLEMENT_DIR}/Logger.c -o ${LOGGER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libLogger.a ${LOGGER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/LoggerTest.c -o ${BUILD_DIR}/LoggerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lLogger -I${HEADERS_DIR}	
	./${BUILD_DIR}/LoggerTest
	${END_MSG} logger

compile_and_test_analyzer: compile_and_test_size_generator compile_and_test_cyclic_list compile_and_test_multi_thread_task_runner compile_and_test_logger compile_and_test_memory_manager
	${START_MSG} analyzer
	${COMPILE_SOURCE} ${ANALYZER_IMPLEMENT_DIR}/AnalyzerAPI.c -o ${ANALYZER_API_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libAnalyzerAPI.a ${ANALYZER_API_OBJECT} ${MEMORY_MANAGER_OBJECT} ${RANDOM_OBJECT} ${TIMER_OBJECT} ${SIZE_GENERATOR} ${MULTI_THREAD_TASK_RUNNER_OBJECT} ${CYCLIC_LIST_OBJECT} ${LOGGER_OBJECT} ${ARRAY_HANDLER_OBJECT} ${SUBHEAP_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/AnalyzerAPITest.c -o ${BUILD_DIR}/AnalyzerAPITest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lAnalyzerAPI -I${HEADERS_DIR} ${MULTI_THREAD_COMPILE_FLAG}	
	./${BUILD_DIR}/AnalyzerAPITest
	${END_MSG} analyzer


########################Collections###################################
	
compile_and_test_key_handler: make_build_dir
	${START_MSG} key_handler
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/KeyHandler.c -o ${KEY_HANDLER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libKeyHandler.a ${KEY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/KeyHandlerTest.c -o ${BUILD_DIR}/KeyHandlerTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR}	 -L${BUILD_DIR} -lKeyHandler
	./${BUILD_DIR}/KeyHandlerTest
	${END_MSG} key_handler
	
compile_and_test_linked_list_handler: compile_and_test_key_handler
	${START_MSG} linked_list_handler
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/LinkedListHandler.c -o ${LINKED_LIST_HANDER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libLinkedListHandler.a ${LINKED_LIST_HANDER_OBJECT} ${KEY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/LinkedListHandlerTest.c -o ${BUILD_DIR}/LinkedListHandlerTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR} -L${BUILD_DIR} -lLinkedListHandler
	./${BUILD_DIR}/LinkedListHandlerTest
	${END_MSG} linked_list_handler

compile_and_test_hash_table: compile_and_test_linked_list_handler compile_and_test_memory_manager compile_and_test_key_handler
	${START_MSG} hash_table
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/HashTable.c -o ${HASH_TABLE_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libHashTable.a ${LINKED_LIST_HANDER_OBJECT} ${HASH_TABLE_OBJECT} ${MEMORY_MANAGER_OBJECT} ${SUBHEAP_HANDLER_OBJECT} ${ARRAY_HANDLER_OBJECT} ${KEY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/HashTableTest.c -o ${BUILD_DIR}/HashTableTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR} -L${BUILD_DIR} -lHashTable
	./${BUILD_DIR}/HashTableTest
	${END_MSG} hash_table

compile_and_test_b_node_handler: compile_and_test_key_handler
	${START_MSG} b_node_handler
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/BNodeHandler.c -o ${B_NODE_HANDER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libBNodeHandler.a ${B_NODE_HANDER_OBJECT} ${KEY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/BNodeHandlerTest.c -o ${BUILD_DIR}/BNodeHandlerTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR} -L${BUILD_DIR} -lBNodeHandler
	./${BUILD_DIR}/BNodeHandlerTest
	${END_MSG} b_node_handler	

compile_and_test_b_tree: compile_and_test_key_handler compile_and_test_memory_manager compile_and_test_b_node_handler
	${START_MSG} b_tree
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/BTree.c -o ${B_TREE_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libBTree.a ${B_TREE_OBJECT} ${B_NODE_HANDER_OBJECT} ${KEY_HANDLER_OBJECT}  ${MEMORY_MANAGER_OBJECT} ${SUBHEAP_HANDLER_OBJECT} ${ARRAY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/BTreeTest.c -o ${BUILD_DIR}/BTreeTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR} -L${BUILD_DIR} -lBTree
	./${BUILD_DIR}/BTreeTest
	${END_MSG} b_tree	

compile_and_test_avl_node_handler: compile_and_test_key_handler
	${START_MSG} avl_node_handler
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/AVLNodeHandler.c -o ${AVL_NODE_HANDER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libAVLNodeHandler.a ${AVL_NODE_HANDER_OBJECT} ${KEY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/AVLNodeHandlerTest.c -o ${BUILD_DIR}/AVLNodeHandlerTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR} -L${BUILD_DIR} -lAVLNodeHandler
	./${BUILD_DIR}/AVLNodeHandlerTest
	${END_MSG} avl_node_handler	

compile_and_test_avl_tree: compile_and_test_key_handler compile_and_test_memory_manager compile_and_test_avl_node_handler
	${START_MSG} avl_tree
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/AVLTree.c -o ${AVL_TREE_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libAVLTree.a ${AVL_TREE_OBJECT} ${AVL_NODE_HANDER_OBJECT} ${KEY_HANDLER_OBJECT}  ${MEMORY_MANAGER_OBJECT} ${SUBHEAP_HANDLER_OBJECT} ${ARRAY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/AVLTreeTest.c -o ${BUILD_DIR}/AVLTreeTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR} -L${BUILD_DIR} -lAVLTree
	./${BUILD_DIR}/AVLTreeTest
	${END_MSG} avl_tree	

########################Network gateway###################################	
compile_and_test_key_generator: compile_and_test_key_handler compile_and_test_random
	${START_MSG} key_generator
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/KeyGenerator.c -o ${KEY_GENERATOR_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libKeyGenerator.a ${KEY_GENERATOR_OBJECT} ${RANDOM_OBJECT} ${TIMER_OBJECT} ${KEY_HANDLER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/KeyGeneratorTest.c -o ${BUILD_DIR}/KeyGeneratorTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR}	 -L${BUILD_DIR} -lKeyGenerator
	./${BUILD_DIR}/KeyGeneratorTest
	${END_MSG} key_generator
	
compile_and_test_fake_transmitters: compile_and_test_key_generator
	${START_MSG} fake_transmitters
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/FakeTransmitters.c -o ${FAKE_TRANSMITTERS_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libFakeTransmitters.a ${KEY_GENERATOR_OBJECT} ${RANDOM_OBJECT} ${TIMER_OBJECT} ${KEY_HANDLER_OBJECT} ${FAKE_TRANSMITTERS_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/FakeTransmittersTest.c -o ${BUILD_DIR}/FakeTransmittersTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR}	 -L${BUILD_DIR} -lFakeTransmitters
	./${BUILD_DIR}/FakeTransmittersTest
	${END_MSG} fake_transmitters
		
compile_and_test_client_server: make_build_dir
	${START_MSG} client_server
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/ClientServer.c -o ${CLIENT_SERVER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libClientServer.a ${CLIENT_SERVER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/ClientServerTest.c -o ${BUILD_DIR}/ClientServerTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR} -L${BUILD_DIR} -lClientServer
	./${BUILD_DIR}/ClientServerTest
	${END_MSG} client_server

compile_and_test_message_handler: compile_and_test_logger compile_and_test_timer compile_and_test_key_handler
	${START_MSG} message_handler
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/MessageHandler.c -o ${MESSAGE_HANDLER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libMessageHandler.a ${MESSAGE_HANDLER_OBJECT} ${KEY_HANDLER_OBJECT} ${LOGGER_OBJECT} ${TIMER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/MessageHandlerTest.c -o ${BUILD_DIR}/MessageHandlerTest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR} -L${BUILD_DIR} -lMessageHandler
	./${BUILD_DIR}/MessageHandlerTest
	${END_MSG} message_handler
	
compile_and_test_network_gateway_api: compile_and_test_logger compile_and_test_fake_transmitters compile_and_test_message_handler compile_and_test_hash_table compile_and_test_message_handler compile_and_test_memory_manager compile_and_test_client_server compile_and_test_avl_tree compile_and_test_b_tree
	${START_MSG} network_gateway_api 
	${COMPILE_SOURCE} ${NETWORK_GATEWAY_DIR}/NetworkGatewayAPI.c -o ${NETWORK_GATEWAY_API_OBJECT} -I${HEADERS_DIR}
	${ARCHIVE} ${BUILD_DIR}/libNetworkGatewayAPI.a ${NETWORK_GATEWAY_API_OBJECT} ${LOGGER_OBJECT} ${KEY_GENERATOR_OBJECT} ${RANDOM_OBJECT} ${TIMER_OBJECT} ${KEY_HANDLER_OBJECT} ${FAKE_TRANSMITTERS_OBJECT} ${LINKED_LIST_HANDER_OBJECT} ${HASH_TABLE_OBJECT} ${MEMORY_MANAGER_OBJECT} ${SUBHEAP_HANDLER_OBJECT} ${ARRAY_HANDLER_OBJECT} ${MESSAGE_HANDLER_OBJECT} ${KEY_HANDLER_OBJECT} ${LOGGER_OBJECT} ${TIMER_OBJECT} ${CLIENT_SERVER_OBJECT} ${AVL_TREE_OBJECT} ${AVL_NODE_HANDER_OBJECT} ${B_TREE_OBJECT} ${B_NODE_HANDER_OBJECT}
	${COMPILE_TEST} ${TEST_DIR}/NetworkGatewayAPITest.c -o ${BUILD_DIR}/NetworkGatewayAPITest -I${TEST_FRMAWORK_DIR} -I${HEADERS_DIR} -L${BUILD_DIR} -lNetworkGatewayAPI  ${MULTI_THREAD_COMPILE_FLAG}
	./${BUILD_DIR}/NetworkGatewayAPITest
	${END_MSG} network_gateway_api
