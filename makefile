all: clean make_build_dir compile_test run clean

make_build_dir:
	mkdir build

compile_test:
	gcc src/main/ArrayHandler.c src/test/MainTest.c -o build/test -Ilib 

run:
	./build/test

clean:
	rm -rf build
