$CompileAR = ar -crsv build/ArrayHandler.a build/ArrayHandler.o

all: run_array_handler_test

make_build_dir: clean
	mkdir build

compile_array_handler: make_build_dir
	gcc -c src/main/implement/ArrayHandler.c -o build/ArrayHandler.o 
	
compile_array_handler_test: compile_array_handler
	gcc -DEBUG -g build/ArrayHandler.o src/test/ArrayHandlerTest.c -o build/ArrayHandlerTest -Ilib -Isrc/main/header

run_array_handler_test: compile_array_handler_test
	./build/ArrayHandlerTest

clean:
	rm -rf build

fork: make_build_dir
	gcc src/test/ForkExample.c -o build/fork
	./build/fork
