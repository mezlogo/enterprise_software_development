all: clean make_build_dir compile_unit_test

make_build_dir: clean
	mkdir build

compile_memory_manager: make_build_dir
	gcc src/main/ArrayHandler.c src/main/MemoryManager.c -o build/main -Isrc/main

compile_unit_test: make_build_dir
	gcc src/main/ArrayHandler.c src/test/MainTest.c -o build/test -Ilib -Isrc/main

test: compile_unit_test
	./build/test

clean:
	rm -rf build

fork: make_build_dir
	gcc src/test/ForkExample.c -o build/fork
	./build/fork