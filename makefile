
CC = gcc
CFLAGS = -g -Wall

default: shell

shell: daShell.c 
	$(CC) $(CFLAGS) -o shell daShell.c 

clean:
	rm -f shell *.o
