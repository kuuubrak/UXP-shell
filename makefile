CC = gcc
CFLAGS = -Wall -std=c99
SOURCES = $(wildcard src/*.c) $(wildcard src/commands/*.c)
OBJECTS = $(SOURCES:.c=.o)
EXEC = uxp-shell

$(EXEC) : $(OBJECTS)
	$(CC) $(OBJECTS) -o $(EXEC)

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	find . -type f -name '*.o' -exec rm {} +
	rm -f uxp-shell
