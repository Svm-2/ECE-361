CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra -I.
 
.PHONY: all test clean
 
all: events
 
events: events.o tally.o
	$(CC) $(CFLAGS) -o events events.o tally.o
 
events.o: events.c tally.h
	$(CC) $(CFLAGS) -c events.c -o events.o
 
tally.o: tally.c tally.h
	$(CC) $(CFLAGS) -c tally.c -o tally.o
 
tests/test_tally.o: tests/test_tally.c tally.h
	$(CC) $(CFLAGS) -c tests/test_tally.c -o tests/test_tally.o
 
tests/test_tally: tests/test_tally.o tally.o
	$(CC) $(CFLAGS) -o tests/test_tally tests/test_tally.o tally.o
 
test: tests/test_tally
	./tests/test_tally
 
clean:
	rm -f events tests/test_tally *.o tests/*.o