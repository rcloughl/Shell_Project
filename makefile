//work in progress

CC = gcc
CFLAGS = -g -Wall

default: shell

shell: main.o proc.o
	$(CC) $(CFLAGS) -o shell main.o proc.o

main.o: main.c types.h defs.h
	$(CC) $(CFLAGS) -c main.c

proc.o: proc.c types.h defs.h proc.h
	$(CC) $(CFLAGS) -c proc.c

clean:
	rm -f shell *.o
