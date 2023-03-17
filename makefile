
CC = gcc
CFLAGS = -g -Wall

default: shell ls cat

shell: daShell.c 
	$(CC) $(CFLAGS) -o shell daShell.c 

ls: ls.c 
	$(CC) $(CFLAGS) -o ls ls.c 

cat: cat.c 
	$(CC) $(CFLAGS) -o cat cat.c 

clean:
	rm -f shell *.o