CC=gcc
CFLAGS=-I.

all: main test

main: main.c interpreter.c ast.h interpreter.h
	$(CC) -o main main.c interpreter.c $(CFLAGS)

test: test.c interpreter.c ast.h interpreter.h
	$(CC) -o test test.c interpreter.c $(CFLAGS)

clean:
	rm -f main test