all: a1.1-system_calls a1.2-fork a1.2-fork3 a1.2-fork4 a1.3-comm

CC = gcc
#CFLAGS = -Wall -O2
#CFLAGS =  -O2

a1.1-system_calls: a1.1-system_calls.o
		$(CC) $(CFLAGS) $^ -o $@

a1.2-fork: a1.2-fork.o
		$(CC) $(CFLAGS) $^ -o $@

a1.2-fork3: a1.2-fork3.o
		$(CC) $(CFLAGS) $^ -o $@

a1.2-fork4: a1.2-fork4.o
		$(CC) $(CFLAGS) $^ -o $@

a1.3-comm: a1.3-comm.o
		$(CC) $(CFLAGS) $^ -o $@

clean:
	rm -f *.o a1.1-system_calls a1.2-fork a1.2-fork3 a1.2-fork4 a1.3-comm