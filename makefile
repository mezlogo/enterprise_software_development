all: make_build_dir compile_test run clean

make_build_dir:
	mkdir build

compile_test:
	gcc src/main/someUseful.c src/test/minunit_example.c -o build/test -Ilib 

run:
	./build/test

clean:
	rm -rf build
