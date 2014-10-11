CC      = gcc
CFLAGS  = -g -o
RM      = rm -rf
RESULT  = main.o
SOURCE  = main.c

.PHONY: all main run clean compile_test
all: clean main run clean 

main: 
	$(CC) $(CFLAGS) $(RESULT) $(SOURCE) 

run:
	./$(RESULT)

clean:
	$(RM) $(RESULT)

compile_test:
	$(CC) mytest.c lib/CUnit/Sources/Basic/Basic.c 


