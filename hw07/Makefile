CC      ?= cc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -g
SAN     =
SANFLAGS = -fsanitize=address,undefined -fno-sanitize-recover=all -fno-omit-frame-pointer

BINS = balance tests/test_istack

all: $(BINS)

balance: balance.c istack.c istack.h
	$(CC) $(CFLAGS) $(SAN) -o $@ balance.c istack.c

tests/test_istack: tests/test_istack.c istack.c istack.h
	$(CC) $(CFLAGS) $(SAN) -I. -o $@ tests/test_istack.c istack.c

test: $(BINS)
	./tests/test_istack
	sh ./regress.sh

memcheck:
	$(MAKE) clean
	$(MAKE) test SAN="$(SANFLAGS)"
	$(MAKE) clean

clean:
	rm -rf $(BINS) *.o tests/*.o *.dSYM tests/*.dSYM

.PHONY: all test memcheck clean
