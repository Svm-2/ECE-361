#include <stdio.h>
#include <string.h>
#include "tally.h"
 
static int total = 0;
static int failed = 0;
 
static void check(int ok, const char *what){
    total++;
    if (ok) {
        printf("PASS: %s\n", what);
    } else {
        failed++;
        printf("FAIL: %s\n", what);
    }
}
 
static void test_counting_up(void){
    tally_t *t = tally_create();
    check(tally_add(t, "door") == 1, "first add returns 1");
    check(tally_add(t, "door") == 2, "second add returns 2");
    check(tally_count(t, "door") == 2, "count matches number of adds");
    check(tally_size(t) == 1, "size counts different names");
    tally_destroy(t);
}
 
static void test_never_added(void){
    tally_t *t = tally_create();
    tally_add(t, "door");
    check(tally_count(t, "window") == 0, "name never added has count 0");
    tally_destroy(t);
}
 
static void test_empty_name(void){
    tally_t *t = tally_create();
    check(tally_add(t, "") == -1, "empty name is refused");
    tally_destroy(t);
}
 
static void test_name_length(void){
    char exact[TALLY_LEN + 1];       /* TALLY_LEN chars + '\0' */
    char too_long[TALLY_LEN + 2];    /* TALLY_LEN + 1 chars + '\0' */
 
    memset(exact, 'a', TALLY_LEN);
    exact[TALLY_LEN] = '\0';
    memset(too_long, 'b', TALLY_LEN + 1);
    too_long[TALLY_LEN + 1] = '\0';
 
    tally_t *t = tally_create();
    check(tally_add(t, exact) == 1, "name of exactly TALLY_LEN chars is accepted");
    check(tally_add(t, too_long) == -1, "name of TALLY_LEN + 1 chars is refused");
    tally_destroy(t);
}
 
static void test_null_arguments(void){
    tally_t *t = tally_create();
    check(tally_add(NULL, "door") == -1, "add with NULL tally returns -1");
    check(tally_add(t, NULL) == -1, "add with NULL name returns -1");
    check(tally_count(NULL, "door") == 0, "count with NULL tally returns 0");
    check(tally_count(t, NULL) == 0, "count with NULL name returns 0");
    check(tally_size(NULL) == 0, "size of NULL returns 0");
    tally_destroy(NULL);
    check(1, "destroy(NULL) does nothing");
    tally_destroy(t);
}
 
static void test_full_tally(void)
{
    char name[32];
    tally_t *t = tally_create();
 
    for (int i = 0; i < TALLY_NAMES; i++) {
        snprintf(name, sizeof name, "name%02d", i);
        tally_add(t, name);
    }
    check(tally_add(t, "brandnew") == -1, "new name in a full tally is refused");
    check(tally_add(t, "name03") == 2, "existing name in a full tally still counts");
    tally_destroy(t);
}
 
static void test_max_tallies(void){
    tally_t *ts[TALLY_MAX];
    int all_ok = 1;
 
    for (int i = 0; i < TALLY_MAX; i++) {
        ts[i] = tally_create();
        if (ts[i] == NULL) {
            all_ok = 0;
        }
    }
    check(all_ok, "TALLY_MAX tallies can be created");
    check(tally_create() == NULL, "one more than TALLY_MAX returns NULL");
 
    for (int i = 0; i < TALLY_MAX; i++) {
        tally_destroy(ts[i]);
    }
}
 
static void test_create_after_destroy(void){
    tally_t *ts[TALLY_MAX];
    for (int i = 0; i < TALLY_MAX; i++) {
        ts[i] = tally_create();
    }
    tally_add(ts[1], "door");
    tally_destroy(ts[1]);
 
    tally_t *again = tally_create();
    check(again != NULL, "create works again after a destroy");
    check(tally_size(again) == 0, "reused tally starts empty");
 
    for (int i = 0; i < TALLY_MAX; i++) {
        if (i != 1) {
            tally_destroy(ts[i]);
        }
    }
    tally_destroy(again);
}
 
static void test_independent(void){
    tally_t *a = tally_create();
    tally_t *b = tally_create();
 
    tally_add(a, "door");
    tally_add(a, "door");
    tally_add(b, "door");
 
    check(tally_count(a, "door") == 2 && tally_count(b, "door") == 1,
          "two tallies are independent");
 
    tally_destroy(a);
    tally_destroy(b);
}
 
static void test_print_order(void){
    const char *expected = "apple 2\nkiwi 1\nmango 1\npear 1\n";
    char buf[256] = {0};
 
    tally_t *t = tally_create();
    tally_add(t, "pear");    /* goes in an empty tally */
    tally_add(t, "apple");   /* goes at the front */
    tally_add(t, "mango");   /* goes in the middle */
    tally_add(t, "kiwi");    /* goes in the middle */
    tally_add(t, "apple");
 
    /* print into a temporary file, then read it back to compare */
    FILE *f = tmpfile();
    if (f != NULL) {
        tally_print(t, f);
        rewind(f);
        size_t len = fread(buf, 1, sizeof buf - 1, f);
        buf[len] = '\0';
        fclose(f);
    }
    check(f != NULL && strcmp(buf, expected) == 0,
          "print lists names in strcmp order as 'name count'");
 
    tally_destroy(t);
}
 
int main(void){
    test_counting_up();
    test_never_added();
    test_empty_name();
    test_name_length();
    test_null_arguments();
    test_full_tally();
    test_max_tallies();
    test_create_after_destroy();
    test_independent();
    test_print_order();
 
    printf("\n%d of %d tests passed", total - failed, total);
    if (failed > 0) {
        printf(", %d FAILED\n", failed);
        return 1;
    }
    printf("\n");
    return 0;
}