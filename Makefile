# This is a comment line
CC=g++
# CFLAGS will be the options passed to the compiler.
CFLAGS= -c -Wall

all: tetris

tetris: main.o piece.o
	$(CC) main.o piece.o -o tetris

main.o: main.cpp
	$(CC) $(CFLAGS) main.cpp

piece.o: piece.cpp
	$(CC) $(CFLAGS) piece.cpp

clean:
	rm -rf *.o 