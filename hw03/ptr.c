#include <stdio.h>
#include "ptr.h"

void swap_float(float *a, float *b){
    float temp = *a;
    *a = *b;
    *b = temp;
}

int minmax(const float *a, int n, float *min, float *max)
{
    if (a == NULL || min == NULL || max == NULL || n < 1)
        return -1;

    float lo = *a;
    float hi = *a;
    for (const float *p = a + 1; p < a + n; p++) {
        if (*p < lo){
            lo = *p;
        }
        if (*p > hi){
            hi = *p;
        }
    }
    *min = lo;
    *max = hi;
    return 0;
}

const float *find_above(const float *a, int n, float threshold)
{
    if (a == NULL || n < 1)
        return NULL;

    for (const float *p = a; p < a + n; p++) {
        if (*p > threshold)
            return p;
    }
    return NULL;
}

void reverse(float *a, int n)
{
    if (a == NULL || n < 2)
        return;

    float *left = a;
    float *right = a + n - 1;
    while (left < right) {
        swap_float(left, right);
        left++;
        right--;
    }
}