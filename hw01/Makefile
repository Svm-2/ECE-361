CC = gcc
CFLAGS = -std=c11 -Wall -Wextra -I.

OBJS = bits.o status.o

all: $(OBJS)

test: $(OBJS) tests/test_bits.o
	$(CC) $(CFLAGS) -o tests/test_bits $(OBJS) tests/test_bits.o
	./tests/test_bits

tests/test_bits.o: tests/test_bits.c
	$(CC) $(CFLAGS) -c tests/test_bits.c -o tests/test_bits.o

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o tests/test_bits tests/test_bits.o

.PHONY: all test clean