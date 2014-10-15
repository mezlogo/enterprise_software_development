all: clean make_build_dir compile compile_test 

build_run: clean make_build_dir compile compile_test run clean

make_build_dir:
	mkdir build

compile:
	gcc -DDEBUG -g src/main/ArrayHandler.c src/main/MemoryManager.c -o build/main -Isrc/main

compile_test:
	gcc -DDEBUG -g src/main/ArrayHandler.c src/test/MainTest.c -o build/test -Ilib -Isrc/main

run:
	./build/test

clean:
	rm -rf build
