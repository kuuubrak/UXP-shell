CC = gcc  

all: clean main.o parser.o
	$(CC) main.o parser.o -o uxp-shell
main.o: main.c
	$(CC) main.c -c -o main.o

parser.o: parser.c
	$(CC) parser.c -c -o parser.o

clean:
	rm -f *.o uxp-shell