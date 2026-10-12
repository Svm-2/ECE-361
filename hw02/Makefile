CC     = gcc
CFLAGS = -std=c11 -Wall -Wextra

OBJS = main.o reading.o stats.o histogram.o

readings: $(OBJS)
	$(CC) $(CFLAGS) -o readings $(OBJS)

main.o: main.c reading.h stats.h histogram.h
	$(CC) $(CFLAGS) -c main.c

reading.o: reading.c reading.h
	$(CC) $(CFLAGS) -c reading.c

stats.o: stats.c stats.h
	$(CC) $(CFLAGS) -c stats.c

histogram.o: histogram.c histogram.h
	$(CC) $(CFLAGS) -c histogram.c

test_stats: tests/test_stats.c stats.o
	$(CC) $(CFLAGS) -o test_stats tests/test_stats.c stats.o

test: readings test_stats
	./test_stats
	sh regress.sh

clean:
	rm -f readings test_stats $(OBJS)