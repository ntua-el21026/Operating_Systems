#
# Makefile
# 

CC = gcc

# CAUTION: Always use '-pthread' when compiling POSIX threads-based
# applications, instead of linking with "-lpthread" directly.
CFLAGS = -Wall -O2 -pthread
LIBS = 

all: mandel-fork1 mandel-fork2


## Mandel

mandel-fork1: mandel-lib.o mandel-fork1.o
	$(CC) $(CFLAGS) -o mandel-fork1 mandel-lib.o mandel-fork1.o $(LIBS)

mandel-fork2: mandel-lib.o mandel-fork2.o
	$(CC) $(CFLAGS) -o mandel-fork2 mandel-lib.o mandel-fork2.o $(LIBS)

mandel-lib.o: mandel-lib.h mandel-lib.c
	$(CC) $(CFLAGS) -c -o mandel-lib.o mandel-lib.c $(LIBS)

mandel-fork1.o: mandel-fork1.c
	$(CC) $(CFLAGS) -c -o mandel-fork1.o mandel-fork1.c $(LIBS)

mandel-fork2.o: mandel-fork2.c
	$(CC) $(CFLAGS) -c -o mandel-fork2.o mandel-fork2.c $(LIBS)

clean:
	rm -f *.s *.o mandel-fork1 mandel-fork2 
