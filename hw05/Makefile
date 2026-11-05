CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -g

all: lock

lock: main.o lock.o
	$(CC) $(CFLAGS) -o $@ main.o lock.o

main.o: main.c lock.h
	$(CC) $(CFLAGS) -c main.c -o $@

lock.o: lock.c lock.h
	$(CC) $(CFLAGS) -c lock.c -o $@

tests/test_lock.o: tests/test_lock.c lock.h
	$(CC) $(CFLAGS) -I. -c tests/test_lock.c -o $@

tests/test_lock: tests/test_lock.o lock.o
	$(CC) $(CFLAGS) -o $@ tests/test_lock.o lock.o

test: tests/test_lock
	./tests/test_lock

clean:
	rm -f lock *.o tests/test_lock tests/*.o

.PHONY: all test clean