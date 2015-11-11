CC = gcc
CFLAG=-Wall -g

all: build bin

build: main.o determineFunctions.o readFile.o writeFile.o operations.o
	$(CC) $(CFLAG) -o bmptool main.o determineFunctions.o readFile.o writeFile.o operations.o

main.o: main.c header.h
	$(CC) $(CFLAG) -c main.c

determineFunctions.o: determineFunctions.c header.h
	$(CC) $(CFLAG) -c determineFunctions.c

readFile.o: readFile.c header.h
	$(CC) $(CFLAG) -c readFile.c

writeFile.o: writeFile.c header.h
	$(CC) $(CFLAG) -c writeFile.c

operations.o: operations.c header.h
	$(CC) $(CFLAG) -c operations.c

bin:
	mkdir bin
	mv *.o bin/

clean:
	rm -rf *.o bin bmptool
