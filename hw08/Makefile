
CC      = cc
CFLAGS  = -std=c11 -Wall -Wextra -Wpedantic -g -I.
SAN     = -fsanitize=address,undefined -fno-omit-frame-pointer

.PHONY: all test memcheck bonus clean

all: treestats test_bst

treestats: treestats.c bst.c bst.h
	$(CC) $(CFLAGS) -o $@ treestats.c bst.c

test_bst: tests/test_bst.c bst.c bst.h
	$(CC) $(CFLAGS) -o $@ tests/test_bst.c bst.c

test: test_bst
	./test_bst

memcheck: tests/test_bst.c treestats.c bst.c bst.h
	$(CC) $(CFLAGS) $(SAN) -o test_bst_san tests/test_bst.c bst.c
	$(CC) $(CFLAGS) $(SAN) -o treestats_san treestats.c bst.c
	./test_bst_san
	printf '27 14 35 10 19 31 42\n' | ./treestats_san
	printf '' | ./treestats_san

bonus: tests/test_remove.c bst.c bst.h
	$(CC) $(CFLAGS) $(SAN) -o test_remove tests/test_remove.c bst.c
	./test_remove

clean:
	rm -f treestats test_bst test_bst_san treestats_san test_remove *.o
	rm -rf *.dSYM
