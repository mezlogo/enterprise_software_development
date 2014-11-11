all: clean make_build_dir compile_unit_test

make_build_dir: clean
	mkdir build

compile_memory_manager: make_build_dir
	gcc src/main/ArrayHandler.c src/main/MemoryManager.c -o build/main -Isrc/main

compile_unit_test: make_build_dir
	gcc src/main/ArrayHandler.c src/test/ArrayHandlerTest.c -o build/ArrayHandlerTest -Ilib -Isrc/main

test: compile_unit_test
	./build/ArrayHandlerTest

clean:
	rm -rf build

fork: make_build_dir
	gcc src/test/ForkExample.c -o build/fork
	./build/fork