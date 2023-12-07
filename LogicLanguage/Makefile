CC = gcc
CFLAGS = -Wall -Wextra -g
LDFLAGS =
OBJ = ast.o lexer.o parser.o interpreter.o main.o
TARGET = logic_compiler

all: $(TARGET)

$(TARGET): $(OBJ)
	$(CC) $(LDFLAGS) -o $@ $^

%.o: %.c
	$(CC) $(CFLAGS) -c -o $@ $<

lexer.o: lexer.c parser.h

lexer.c: lexer.l
	flex -o $@ $^

parser.c parser.h: parser.y
	bison -d -o parser.c $^

clean:
	rm -f $(OBJ) $(TARGET) lexer.c parser.c parser.h

.PHONY: all clean