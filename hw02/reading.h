#ifndef READING_H
#define READING_H
#define LINE_LEN 128
#define MAX_READINGS 1000

/*Takes inputs ticks, temps, hums, and skipped. Reads from stdin and fills the arrays with readings. Returns the number of readings read. Assumes MAX_READINGS is non-null number */
int reading_read(int ticks[], float temps[], float hums[], int *skipped);

#endif /* READING_H */