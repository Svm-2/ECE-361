#include <stdio.h>
#include <stdlib.h>

#include "istack.h"

#define CHECK(cond)                                                       \
    do {                                                                  \
        if (!(cond)) {                                                    \
            printf("    check failed: %s (line %d)\n", #cond, __LINE__);  \
            ok = 0;                                                       \
        }                                                                 \
    } while (0)

static int test_empty_pop_peek_leave_v_alone(void)
{
    int ok = 1;
    istack_t *s = istack_create();
    int v = 12345;
    CHECK(istack_pop(s, &v) == -1);
    CHECK(v == 12345);
    CHECK(istack_peek(s, &v) == -1);
    CHECK(v == 12345);
    CHECK(istack_pop(s, NULL) == -1);
    CHECK(istack_peek(s, NULL) == -1);
    istack_destroy(s);
    return ok;
}

static int test_lifo(void)
{
    int ok = 1;
    istack_t *s = istack_create();
    CHECK(istack_push(s, 1) == 0);
    CHECK(istack_push(s, 2) == 0);
    CHECK(istack_push(s, 3) == 0);
    int v = 0;
    CHECK(istack_peek(s, &v) == 0 && v == 3);
    CHECK(istack_count(s) == 3);
    CHECK(istack_pop(s, &v) == 0 && v == 3);
    CHECK(istack_pop(s, &v) == 0 && v == 2);
    CHECK(istack_pop(s, NULL) == 0);
    CHECK(istack_is_empty(s));
    istack_destroy(s);
    return ok;
}

static int test_full_at_8_then_doubles(void)
{
    int ok = 1;
    istack_t *s = istack_create();
    for (int i = 0; i < 8; i++)
        CHECK(istack_push(s, i * 10) == 0);
    CHECK(istack_count(s) == 8);
    CHECK(istack_capacity(s) == 8);

    CHECK(istack_push(s, 80) == 0);
    CHECK(istack_count(s) == 9);
    CHECK(istack_capacity(s) == 16);

    for (int i = 8; i >= 0; i--) {
        int v = -1;
        CHECK(istack_pop(s, &v) == 0 && v == i * 10);
    }
    CHECK(istack_capacity(s) == 16);
    istack_destroy(s);
    return ok;
}

static int test_1000_push_pop(void)
{
    int ok = 1;
    istack_t *s = istack_create();
    for (int i = 0; i < 1000; i++)
        CHECK(istack_push(s, i) == 0);
    CHECK(istack_count(s) == 1000);
    CHECK(istack_capacity(s) == 1024);
    for (int i = 999; i >= 0; i--) {
        int v = -1;
        CHECK(istack_pop(s, &v) == 0 && v == i);
    }
    CHECK(istack_is_empty(s));
    CHECK(istack_capacity(s) == 1024);
    istack_destroy(s);
    return ok;
}

static int test_to_array_bottom_first_and_copy(void)
{
    int ok = 1;
    istack_t *s = istack_create();
    for (int i = 1; i <= 10; i++)
        istack_push(s, i);

    size_t n = 999;
    int *a = istack_to_array(s, &n);
    CHECK(a != NULL);
    CHECK(n == 10);
    if (a != NULL && n == 10) {
        for (size_t i = 0; i < n; i++)
            CHECK(a[i] == (int)i + 1);

        a[9] = -7;
        int v = 0;
        CHECK(istack_peek(s, &v) == 0 && v == 10);

        istack_pop(s, NULL);
        CHECK(a[9] == -7);
        CHECK(istack_count(s) == 9);
    }
    free(a);

    istack_t *e = istack_create();
    n = 999;
    CHECK(istack_to_array(e, &n) == NULL);
    CHECK(n == 0);
    istack_destroy(e);
    istack_destroy(s);
    return ok;
}

static int test_null_arguments(void)
{
    int ok = 1;
    int v = 42;
    size_t n = 99;
    CHECK(istack_push(NULL, 1) == -1);
    CHECK(istack_pop(NULL, &v) == -1 && v == 42);
    CHECK(istack_peek(NULL, &v) == -1 && v == 42);
    CHECK(istack_count(NULL) == 0);
    CHECK(istack_is_empty(NULL) == true);
    CHECK(istack_capacity(NULL) == 0);
    CHECK(istack_to_array(NULL, &n) == NULL && n == 0);
    istack_destroy(NULL);
    return ok;
}

static int test_two_stacks_independent(void)
{
    int ok = 1;
    istack_t *a = istack_create();
    istack_t *b = istack_create();
    for (int i = 0; i < 20; i++)
        istack_push(a, i);
    istack_push(b, 100);

    CHECK(istack_count(a) == 20);
    CHECK(istack_count(b) == 1);
    CHECK(istack_capacity(a) == 32);
    CHECK(istack_capacity(b) == 8);

    int v = 0;
    CHECK(istack_pop(b, &v) == 0 && v == 100);
    CHECK(istack_peek(a, &v) == 0 && v == 19);
    CHECK(istack_is_empty(b));
    CHECK(istack_count(a) == 20);
    istack_destroy(a);
    istack_destroy(b);
    return ok;
}

static int test_destroy_not_empty(void)
{
    int ok = 1;
    istack_t *s = istack_create();
    for (int i = 0; i < 100; i++)
        CHECK(istack_push(s, i) == 0);
    istack_destroy(s);
    return ok;
}

struct test {
    const char *name;
    int (*fn)(void);
};

int main(void)
{
    const struct test tests[] = {
        { "pop/peek on empty leave *v alone",          test_empty_pop_peek_leave_v_alone },
        { "last in, first out",                        test_lifo },
        { "full at 8, 9th push doubles to 16",         test_full_at_8_then_doubles },
        { "1000 pushes and pops",                      test_1000_push_pop },
        { "to_array is bottom first and a copy",       test_to_array_bottom_first_and_copy },
        { "NULL arguments",                            test_null_arguments },
        { "two stacks are independent",                test_two_stacks_independent },
        { "destroy a stack that is not empty",         test_destroy_not_empty },
    };
    const size_t ntests = sizeof tests / sizeof tests[0];
    size_t passed = 0;

    for (size_t i = 0; i < ntests; i++) {
        int ok = tests[i].fn();
        printf("%s: %s\n", ok ? "PASS" : "FAIL", tests[i].name);
        if (ok)
            passed++;
    }
    printf("%zu of %zu tests passed\n", passed, ntests);
    return passed == ntests ? EXIT_SUCCESS : EXIT_FAILURE;
}
