#ifndef HISTOGRAM_H
#define HISTOGRAM_H
#define NUM_BINS     20          /* histogram: 0 to 100 C in 5 C bins */
#define BIN_WIDTH    5.0f

//Print historgram of array a of size n
void histogram_print(const float a[], int n);

#endif /* HISTOGRAM_H */