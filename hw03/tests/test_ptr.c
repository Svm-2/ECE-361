#include <stdio.h>
#include <stdlib.h>
#include "../ptr.h"

static int passed = 0;
static int failed = 0;

static void check(int ok, const char *name)
{
    if (ok) {
        printf("PASS  %s\n", name);
        passed++;
    } else {
        printf("FAIL  %s\n", name);
        failed++;
    }
}

/* Returns 1 if a[0..n-1] equals b[0..n-1] exactly. */
static int same(const float *a, const float *b, int n)
{
    for (int i = 0; i < n; i++)
        if (a[i] != b[i])
            return 0;
    return 1;
}

static void test_swap_float(void)
{
    float x = 1.5f, y = -2.0f;
    swap_float(&x, &y);
    check(x == -2.0f && y == 1.5f, "swap_float exchanges two values");

    float z = 3.0f;
    swap_float(&z, &z);
    check(z == 3.0f, "swap_float with the same pointer twice");
}

static void test_minmax(void)
{
    float min = 0.0f, max = 0.0f;

    float many[] = {3.0f, -1.5f, 7.25f, 0.0f, 2.0f};
    int r = minmax(many, 5, &min, &max);
    check(r == 0 && min == -1.5f && max == 7.25f, "minmax on several values");

    float one[] = {4.0f};
    r = minmax(one, 1, &min, &max);
    check(r == 0 && min == 4.0f && max == 4.0f, "minmax on one value");

    min = 111.0f;
    max = 222.0f;
    r = minmax(many, 0, &min, &max);
    check(r == -1 && min == 111.0f && max == 222.0f,
          "minmax with n = 0 returns -1, outputs unchanged");

    r = minmax(NULL, 5, &min, &max);
    check(r == -1 && min == 111.0f && max == 222.0f,
          "minmax with a = NULL returns -1, outputs unchanged");

    r = minmax(many, 5, NULL, &max);
    check(r == -1 && max == 222.0f,
          "minmax with min = NULL returns -1, max unchanged");

    r = minmax(many, 5, &min, NULL);
    check(r == -1 && min == 111.0f,
          "minmax with max = NULL returns -1, min unchanged");
}

static void test_find_above(void)
{
    float a[] = {1.0f, 5.0f, 2.0f, 8.0f};

    const float *p = find_above(a, 4, 4.0f);
    check(p == &a[1], "find_above with two matches returns the first");

    p = find_above(a, 4, 10.0f);
    check(p == NULL, "find_above with no match returns NULL");

    p = find_above(a, 4, 5.0f);
    check(p == &a[3], "find_above skips a value equal to the threshold");

    float eq[] = {5.0f, 5.0f};
    p = find_above(eq, 2, 5.0f);
    check(p == NULL, "find_above with only equal values returns NULL");
}

static void test_reverse(void)
{
    float even[] = {1.0f, 2.0f, 3.0f, 4.0f};
    float even_want[] = {4.0f, 3.0f, 2.0f, 1.0f};
    reverse(even, 4);
    check(same(even, even_want, 4), "reverse on an even length");

    float odd[] = {1.0f, 2.0f, 3.0f, 4.0f, 5.0f};
    float odd_want[] = {5.0f, 4.0f, 3.0f, 2.0f, 1.0f};
    reverse(odd, 5);
    check(same(odd, odd_want, 5), "reverse on an odd length");

    float single[] = {9.0f};
    reverse(single, 1);
    check(single[0] == 9.0f, "reverse with n = 1 does nothing");

    reverse(NULL, 3); /* must not crash */
    check(1, "reverse with a = NULL does nothing");
}

int main(void)
{
    test_swap_float();
    test_minmax();
    test_find_above();
    test_reverse();

    printf("\n%d passed, %d failed, %d total\n",
           passed, failed, passed + failed);
    return failed == 0 ? EXIT_SUCCESS : EXIT_FAILURE;
}