#include "../stats.h"
#include <stdlib.h>
#include <stdio.h>

int main(void) {
    int failed = 0;
    float result;

    /* test 1: one value */
    float a[] = {42.0f};
    result = stats_max(a, 1);
    if (result == 42.0f)
        printf("PASS  stats_max one value\n");
    else {
        printf("FAIL  stats_max one value\n");
        failed++;
    }

     /* test 2: max at start of array */
    float a2[] = {99.0f, 10.0f, 5.0f};
    result = stats_max(a2, 3);
    if (result == 99.0f)
        printf("PASS  stats_max three values at start of array\n");
    else {
        printf("FAIL  stats_max three values at start of array\n");
        failed++;
    }  

      /* test 3: max at end of array */
    float a3[] = {10.0f, 5.0f, 98.0f};
    result = stats_max(a3, 3);
    if (result == 98.0f)
        printf("PASS  stats_max three values at end of array\n");
    else {
        printf("FAIL  stats_max three values at end of array\n");
        failed++;
    }  

   /* test 4: value equal to threshold ends a run */
    float a4[] = {31.0f, 30.0f, 32.0f};
    int run_start, run_len;
    stats_longest_run_above(a4, 3, 30.0f, &run_start, &run_len);
    if (run_len == 1)
        printf("PASS  threshold exact value ends run\n");
    else {
        printf("FAIL  threshold exact value ends run\n");
        failed++;
    }

    /* test 5: recussive max of array of 10,000 */
    float *a5 = malloc(10000 * sizeof(float));
    for (int i = 0; i < 10000; i++){
        a5[i] = (float)i;
    }
    result = stats_max(a5, 10000);
    if (result == 9999.0f)
        printf("PASS  stats_max of 10,000 values\n");
    else {
        printf("FAIL  stats_max of 10,000 values\n");
        failed++;
    }
    free(a5);

    if (failed == 0)
        printf("ALL TESTS PASSED\n");
    else
        printf("%d TESTS FAILED\n", failed);

    return failed;
}