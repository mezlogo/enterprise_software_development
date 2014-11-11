all: clean make_build_dir compile_memory_manager compile_unit_test unit_test clean

make_build_dir: clean
	mkdir build

compile_memory_manager: make_build_dir
	gcc src/main/ArrayHandler.c src/main/MemoryManager.c -o build/main -Isrc/main

compile_unit_test: compile_memory_manager
	gcc -DDEBUG -g src/main/ArrayHandler.c src/test/MainTest.c -o build/test -Ilib -Isrc/main

unit_test: compile_unit_test
	./build/test

clean:
	rm -rf build

fork: make_build_dir
	gcc src/test/ForkExample.c -o build/fork
	./build/fork