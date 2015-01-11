CC = gcc  

all: clean main.o parser.o cd.o mkdir.o
	$(CC) main.o parser.o cd.o mkdir.o -o uxp-shell
main.o: main.c
	$(CC) main.c -c -o main.o

parser.o: parser.c
	$(CC) parser.c -c -o parser.o

cd.o: commands/cd.c
	$(CC) commands/cd.c -c -o cd.o

mkdir.o: commands/mkdir.c
	$(CC) commands/mkdir.c -c -o mkdir.o

clean:
	rm -f *.o uxp-shell