
CC = gcc
CFLAGS = -g -Wall

default: shell ls

shell: daShell.c 
	$(CC) $(CFLAGS) -o shell daShell.c 

ls: ls.c 
	$(CC) $(CFLAGS) -o ls ls.c 

clean:
	rm -f shell *.o