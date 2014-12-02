BUILD_DIR = build
SRC_DIR = src
MAIN_DIR = ${SRC_DIR}/main
TEST_DIR = ${SRC_DIR}/test
HEADERS_DIR = ${MAIN_DIR}/header
MEMORY_MANAGER_IMPLEMENT_DIR = ${MAIN_DIR}/memory_manager
TEST_FRMAWORK_DIR = lib

COMPILE = gcc
ARCHIVE = ar -crsv
RECURSIVE_REMOVE = rm -rf
CREATE_DIRS = mkdir

ARRAY_HANDLER_OBJECT = ${BUILD_DIR}/ArrayHandler.o
SUBHEAP_HANDLER_OBJECT = ${BUILD_DIR}/SubheapHandler.o
MEMORY_MANAGER_OBJECT = ${BUILD_DIR}/MemoryManager.o

START_MSG = @echo "<--------Start compile and testing"
END_MSG = @echo "<--------End compile and testing"

all: compile_and_test_memory_manager

make_build_dir: clean
	${CREATE_DIRS} ${BUILD_DIR}

compile_and_test_array_handler: make_build_dir
	${START_MSG} array_handler
	${COMPILE} -c ${MEMORY_MANAGER_IMPLEMENT_DIR}/ArrayHandler.c -o ${ARRAY_HANDLER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libArrayHandler.a ${ARRAY_HANDLER_OBJECT}
	${COMPILE} -DEBUG -g ${TEST_DIR}/ArrayHandlerTest.c -o ${BUILD_DIR}/ArrayHandlerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lArrayHandler -I${HEADERS_DIR}	
	./${BUILD_DIR}/ArrayHandlerTest
	${END_MSG} array_handler
	
compile_and_test_subheap_handler: make_build_dir
	${START_MSG} subheap_handler
	${COMPILE} -c ${MEMORY_MANAGER_IMPLEMENT_DIR}/SubheapHandler.c -o ${SUBHEAP_HANDLER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libSubheapHandler.a ${SUBHEAP_HANDLER_OBJECT}
	${COMPILE} -DEBUG -g ${TEST_DIR}/SubheapHandlerTest.c -o ${BUILD_DIR}/SubheapHandlerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lSubheapHandler -I${HEADERS_DIR}	
	./${BUILD_DIR}/SubheapHandlerTest
	${END_MSG} subheap_handler
	

compile_and_test_memory_manager: compile_and_test_array_handler compile_and_test_subheap_handler
	${START_MSG} memory_manager
	${COMPILE} -c ${MEMORY_MANAGER_IMPLEMENT_DIR}/MemoryManagerSubheapImpl.c -o ${MEMORY_MANAGER_OBJECT} -I${HEADERS_DIR}	
	${ARCHIVE} ${BUILD_DIR}/libMemoryManager.a ${MEMORY_MANAGER_OBJECT} ${SUBHEAP_HANDLER_OBJECT} ${ARRAY_HANDLER_OBJECT}
	${COMPILE} -DEBUG -g ${TEST_DIR}/MemoryManagerTest.c -o ${BUILD_DIR}/MemoryManagerTest -I${TEST_FRMAWORK_DIR} -L${BUILD_DIR} -lMemoryManager -I${HEADERS_DIR}	
	./${BUILD_DIR}/MemoryManagerTest
	${END_MSG} memory_manager

clean:
	${RECURSIVE_REMOVE} ${BUILD_DIR}

fork: make_build_dir
	${COMPILE} ${TEST_DIR}/ForkExample.c -o ${BUILD_DIR}/fork
	./${BUILD_DIR}/fork
