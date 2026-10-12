#ifndef STATS_H
#define STATS_H

//calculates the minimum value in an array of floats
float stats_min(const float a[], int n);
//calculates the maximum value in an array of floats
float stats_max(const float a[], int n);
//calculates the mean value in an array of floats
float stats_mean(const float a[], int n);
//calculates the longest run of consecutive values above a threshold in an array of floats
void stats_longest_run_above(const float a[], int n, float threshold, int *start_index, int *length);

#endif /* STATS_H */