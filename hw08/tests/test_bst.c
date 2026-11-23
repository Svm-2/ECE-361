#include "bst.h"
#include <stdio.h>

static int failures = 0;

static void check(const char *name, bool ok)
{
    printf("%s: %s\n", ok ? "PASS" : "FAIL", name);
    fflush(stdout);
    if (!ok) {
        failures++;
    }
}

static bst_t *build(const int *keys, size_t n)
{
    bst_t *t = bst_create();
    if (t == NULL) {
        return NULL;
    }
    for (size_t i = 0; i < n; i++) {
        if (bst_insert(t, keys[i]) != 0) {
            bst_destroy(t);
            return NULL;
        }
    }
    return t;
}

static void test_null_tree(void)
{
    size_t visits = 99;

    check("NULL tree: size 0", bst_size(NULL) == 0);
    check("NULL tree: height 0", bst_height(NULL) == 0);
    check("NULL tree: insert returns -1", bst_insert(NULL, 5) == -1);
    check("NULL tree: not found, 0 visits",
          !bst_contains(NULL, 5, &visits) && visits == 0);
    bst_destroy(NULL);
    check("NULL tree: destroy does nothing", true);
}

static void test_seven_keys(void)
{
    const int keys[] = { 27, 14, 35, 10, 19, 31, 42 };
    bst_t *t = build(keys, sizeof keys / sizeof keys[0]);
    size_t visits = 0;

    check("seven keys: tree built", t != NULL);
    if (t == NULL) {
        return;
    }
    check("seven keys: size 7", bst_size(t) == 7);
    check("seven keys: height 3", bst_height(t) == 3);
    check("seven keys: 31 found in 3 visits",
          bst_contains(t, 31, &visits) && visits == 3);
    check("seven keys: 15 not found in 3 visits",
          !bst_contains(t, 15, &visits) && visits == 3);
    check("seven keys: 31 found with visits NULL",
          bst_contains(t, 31, NULL));
    bst_destroy(t);
}

static void test_duplicate(void)
{
    const int keys[] = { 5, 5 };
    bst_t *t = build(keys, sizeof keys / sizeof keys[0]);

    check("duplicate: tree built", t != NULL);
    if (t == NULL) {
        return;
    }
    check("duplicate: kept, size 2", bst_size(t) == 2);
    bst_destroy(t);
}

static void test_increasing(void)
{
    const int keys[] = { 1, 2, 3, 4, 5, 6, 7, 8, 9, 10 };
    const size_t n = sizeof keys / sizeof keys[0];
    bst_t *t = build(keys, n);

    check("increasing: tree built", t != NULL);
    if (t == NULL) {
        return;
    }
    check("increasing: height equals number of keys", bst_height(t) == n);
    bst_destroy(t);
}

static void test_destroy_full(void)
{
    const int keys[] = { 27, 14, 35, 10, 19, 31, 42 };
    bst_t *t = build(keys, sizeof keys / sizeof keys[0]);

    check("destroy full tree: tree built", t != NULL);
    bst_destroy(t);
    check("destroy full tree: returned (memcheck checks for leaks)", true);
}

static void test_empty_search(void)
{
    bst_t *t = bst_create();
    size_t visits = 99;

    check("empty tree: tree created", t != NULL);
    if (t == NULL) {
        return;
    }
    check("empty tree: search finds nothing, 0 visits",
          !bst_contains(t, 42, &visits) && visits == 0);
    bst_destroy(t);
}

int main(void)
{
    test_null_tree();
    test_seven_keys();
    test_duplicate();
    test_increasing();
    test_destroy_full();
    test_empty_search();

    printf("%s: %d failure(s)\n", failures == 0 ? "ALL PASS" : "SOME FAILED", failures);
    return failures == 0 ? 0 : 1;
}