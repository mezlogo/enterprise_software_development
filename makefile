BUILD_DIR = build
SRC_DIR = src
MAIN_DIR = ${SRC_DIR}/main
TEST_DIR = ${SRC_DIR}/test
HEADERS_DIR = ${MAIN_DIR}/header
MEMORY_MANAGER_IMPLEMENT_DIR = ${MAIN_DIR}/memory_manager
TEST_FRMAWORK_DIR = lib

COMPILE = gcc
RECURSIVE_REMOVE = rm -rf
CREATE_DIRS = mkdir

$CompileAR = ar -crsv ${BUILD_DIR}/ArrayHandler.a ${BUILD_DIR}/ArrayHandler.o


ARRAY_HANDLER_OBJECT = ${BUILD_DIR}/ArrayHandler.o

sfsf = gcc ${MEMORY_MANAGER_IMPLEMENT_DIR}/ArrayHandler.c ${MEMORY_MANAGER_IMPLEMENT_DIR}/MemoryManager.c ${TEST_DIR}/MemoryManagerTest.c -o ${BUILD_DIR}/MemoryManagerTest -I${TEST_FRMAWORK_DIR}  -I${HEADERS_DIR}

all: run_array_handler_test

make_build_dir: clean
	${CREATE_DIRS} ${BUILD_DIR}

compile_array_handler: make_build_dir
	${COMPILE} -c ${MEMORY_MANAGER_IMPLEMENT_DIR}/ArrayHandler.c -o ${ARRAY_HANDLER_OBJECT}

make_array_hanlder_lib: compile_array_handler
	ar -crsv ${BUILD_DIR}/libArrayHandler.a ${BUILD_DIR}/ArrayHandler.o
	
compile_array_handler_test: make_array_hanlder_lib
	${COMPILE} -DEBUG -g ${MEMORY_MANAGER_IMPLEMENT_DIR}/nanotime.c ${TEST_DIR}/ArrayHandlerTest.c -o ${BUILD_DIR}/ArrayHandlerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lArrayHandler -I${HEADERS_DIR}

run_array_handler_test: compile_array_handler_test
	./${BUILD_DIR}/ArrayHandlerTest

compile_memory_manager: run_array_handler_test
	${COMPILE} -c ${MEMORY_MANAGER_IMPLEMENT_DIR}/MemoryManager.c -o ${BUILD_DIR}/MemoryManager.o -I${HEADERS_DIR}

make_memory_manager_lib: compile_memory_manager
	ar -crsv ${BUILD_DIR}/libMemoryManager.a ${BUILD_DIR}/MemoryManager.o ${ARRAY_HANDLER_OBJECT}

compile_memory_manager_test: make_memory_manager_lib
	${COMPILE} -DEBUG -g ${TEST_DIR}/MemoryManagerTest.c -o ${BUILD_DIR}/MemoryManagerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lMemoryManager -I${HEADERS_DIR}	

run_memory_manager_test: compile_memory_manager_test
	./${BUILD_DIR}/MemoryManagerTest

clean:
	${RECURSIVE_REMOVE} ${BUILD_DIR}

fork: make_build_dir
	${COMPILE} ${TEST_DIR}/ForkExample.c -o ${BUILD_DIR}/fork
	./${BUILD_DIR}/fork
