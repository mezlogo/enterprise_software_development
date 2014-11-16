$CompileAR = ar -crsv build/ArrayHandler.a build/ArrayHandler.o

ARRAY_HANDLER_OBJECT = build/ArrayHandler.o

sfsf = gcc src/main/implement/ArrayHandler.c src/main/implement/MemoryManager.c src/test/MemoryManagerTest.c -o build/MemoryManagerTest -Ilib  -Isrc/main/header

all: run_memory_manager_test

make_build_dir: clean
	mkdir build

compile_array_handler: make_build_dir
	gcc -c src/main/implement/ArrayHandler.c -o ${ARRAY_HANDLER_OBJECT}

make_array_hanlder_lib: compile_array_handler
	ar -crsv build/libArrayHandler.a build/ArrayHandler.o
	
compile_array_handler_test: make_array_hanlder_lib
	gcc -DEBUG -g src/test/ArrayHandlerTest.c -o build/ArrayHandlerTest -Ilib -Lbuild -lArrayHandler -Isrc/main/header

run_array_handler_test: compile_array_handler_test
	./build/ArrayHandlerTest

compile_memory_manager: run_array_handler_test
	gcc -c src/main/implement/MemoryManager.c -o build/MemoryManager.o -Isrc/main/header

make_memory_manager_lib: compile_memory_manager
	ar -crsv build/libMemoryManager.a build/MemoryManager.o ${ARRAY_HANDLER_OBJECT}

compile_memory_manager_test: make_memory_manager_lib
	gcc -DEBUG -g src/test/MemoryManagerTest.c -o build/MemoryManagerTest -Ilib -Lbuild -lMemoryManager -Isrc/main/header	

run_memory_manager_test: compile_memory_manager_test
	./build/MemoryManagerTest

clean:
	rm -rf build

fork: make_build_dir
	gcc src/test/ForkExample.c -o build/fork
	./build/fork
