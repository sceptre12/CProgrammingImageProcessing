CC = gcc
CFLAG=-Wall -g

all: build bin

build: main.o
	$(CC) $(CFLAG) -o bmptool main.o

main.o: main.c
	$(CC) $(CFLAG) -c main.c

bin:
	mkdir bin
	mv *.o bin/

clean:
	rm -rf bin bmptool
