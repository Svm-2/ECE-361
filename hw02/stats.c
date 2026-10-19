#include "stats.h"

float stats_min(const float a[], int n){
 float tmin = a[0];
    for (int i = 0; i < n; i++) {
        if (a[i] < tmin)
            tmin = a[i];
    }
    return tmin;
}

float stats_max(const float a[], int n){
    if (n == 1){
        return a[0];
    }
    float rest = stats_max(a + 1, n - 1);
    return a[0] > rest ? a[0] : rest;
}

float stats_mean(const float a[], int n){
    float tmean = 0.0f;
    for (int i = 0; i < n; i++) {
        tmean += a[i];
    }
    return tmean/n;
}

void stats_longest_run_above(const float a[], int n, float threshold, int *start_index, int *length){
    int run = 0, best = 0, best_start = -1, start = 0;
    for (int i = 0; i < n; i++) {
        if (a[i] > threshold) {
            if (run == 0)
                start = i;
                run++;
            if (run > best) {
                best = run;
                best_start = start;
            }
        } else {
            run = 0;
        }
    }
    *start_index = best_start;
    *length = best;
}