all: clean make_build_dir compile_test 

f: clean make_build_dir compile_test run clean

make_build_dir:
	mkdir build

compile_test:
	gcc -DDEBUG -g src/main/ArrayHandler.c src/test/MainTest.c -o build/test -Ilib -Isrc/main

run:
	./build/test

clean:
	rm -rf build
