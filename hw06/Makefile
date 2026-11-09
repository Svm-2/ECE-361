CC = gcc
CFLAGS = -std=c11 -Wall -Wextra
LDLIBS = -lm
 
OBJS = main.o sensor.o panel.o scenario.o iom361_r4.o
TEST_OBJS = tests/test_hw06.o sensor.o panel.o scenario.o iom361_r4.o
 
replay: $(OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
 
tests/test_hw06: $(TEST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDLIBS)
 
main.o: main.c scenario.h sensor.h panel.h iom361_r4.h
	$(CC) $(CFLAGS) -c -o $@ $<
 
sensor.o: sensor.c sensor.h iom361_r4.h
	$(CC) $(CFLAGS) -c -o $@ $<
 
panel.o: panel.c panel.h iom361_r4.h
	$(CC) $(CFLAGS) -c -o $@ $<
 
scenario.o: scenario.c scenario.h
	$(CC) $(CFLAGS) -c -o $@ $<
 
iom361_r4.o: iom361_r4.c iom361_r4.h
	$(CC) $(CFLAGS) -c -o $@ $<
 
tests/test_hw06.o: tests/test_hw06.c sensor.h panel.h scenario.h iom361_r4.h
	$(CC) $(CFLAGS) -I. -c -o $@ $<
 
test: replay tests/test_hw06
	./tests/test_hw06
	sh regress.sh
 
clean:
	rm -f replay tests/test_hw06 *.o tests/*.o tests/tmp_scenario.txt
 
.PHONY: test clean