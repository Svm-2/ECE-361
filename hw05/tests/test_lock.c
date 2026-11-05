#include <stdio.h>
#include <string.h>
#include "lock.h"

static int passed = 0;
static int failed = 0;

/* Prints PASS or FAIL for one test and counts it. */
static void check(int ok, const char *what){
    printf("%s: %s\n", ok ? "PASS" : "FAIL", what);
    if(ok){
        passed++;
    }
    else{
        failed++;
    }
}

/* One table entry: from state s on event e, expect next state and action.
   The expected values come from the paper table, not from lock_table. */
static void check_entry(state_t s, event_t e, state_t want_next, action_t want_action){
    action_t a = A_UNDEFINED;
    state_t next = lock_step(s, e, &a);
    char what[80];
    snprintf(what, sizeof what, "%s + %s -> %s %s",
             state_name(s), event_name(e), state_name(want_next), action_name(want_action));
    check(next == want_next && a == want_action, what);
}

/* lock_event: character c in state s should give event want (or -1). */
static void check_event(state_t s, char c, int want){
    char what[80];
    char shown = (c == '\n') ? 'n' : c;
    snprintf(what, sizeof what, "lock_event(%s, '%s%c') == %s",
             state_name(s), c == '\n' ? "\\" : "", shown,
             want == -1 ? "-1" : event_name((event_t)want));
    check(lock_event(s, c) == want, what);
}

/* Runs a whole string of keys from LOCKED, the same way main.c does.
   Returns the final state; *last gets the last action taken. */
static state_t run(const char *keys, action_t *last){
    state_t s = LOCKED;
    *last = A_UNDEFINED;
    for(const char *p = keys; *p != '\0'; p++){
        int e = lock_event(s, *p);
        if(e != -1){
            s = lock_step(s, (event_t)e, last);
        }
    }
    return s;
}

static void test_table(void){
    check_entry(LOCKED, E_RIGHT,   GOT1,   A_NONE);
    check_entry(LOCKED, E_WRONG,   LOCKED, A_BEEP);
    check_entry(LOCKED, E_CLOSE,   LOCKED, A_NONE);
    check_entry(LOCKED, E_TIMEOUT, LOCKED, A_NONE);

    check_entry(GOT1, E_RIGHT,   GOT2,   A_NONE);
    check_entry(GOT1, E_WRONG,   LOCKED, A_BEEP);
    check_entry(GOT1, E_CLOSE,   GOT1,   A_NONE);
    check_entry(GOT1, E_TIMEOUT, LOCKED, A_NONE);

    check_entry(GOT2, E_RIGHT,   OPEN,   A_UNLOCK);
    check_entry(GOT2, E_WRONG,   LOCKED, A_BEEP);
    check_entry(GOT2, E_CLOSE,   GOT2,   A_NONE);
    check_entry(GOT2, E_TIMEOUT, LOCKED, A_NONE);

    check_entry(OPEN, E_RIGHT,   OPEN,   A_NONE);
    check_entry(OPEN, E_WRONG,   OPEN,   A_NONE);
    check_entry(OPEN, E_CLOSE,   LOCKED, A_LOCK);
    check_entry(OPEN, E_TIMEOUT, LOCKED, A_LOCK);
}

static void test_events(void){
    /* a right and a wrong digit in each state */
    check_event(LOCKED, '3', E_RIGHT);
    check_event(LOCKED, '5', E_WRONG);
    check_event(GOT1,   '1', E_RIGHT);
    check_event(GOT1,   '3', E_WRONG);
    check_event(GOT2,   '4', E_RIGHT);
    check_event(GOT2,   '1', E_WRONG);

    /* while open, every digit is wrong: there is no next digit */
    check_event(OPEN, '3', E_WRONG);
    check_event(OPEN, '0', E_WRONG);

    /* c and t mean the same thing in every state */
    check_event(LOCKED, 'c', E_CLOSE);
    check_event(GOT1,   'c', E_CLOSE);
    check_event(OPEN,   'c', E_CLOSE);
    check_event(LOCKED, 't', E_TIMEOUT);
    check_event(GOT2,   't', E_TIMEOUT);
    check_event(OPEN,   't', E_TIMEOUT);

    /* anything else is not an event */
    check_event(LOCKED, 'x', -1);
    check_event(GOT1,   ' ', -1);
    check_event(OPEN,   '\n', -1);
}

static void test_sequences(void){
    action_t last;
    state_t end;

    end = run("314", &last);
    check(end == OPEN && last == A_UNLOCK, "3 1 4 opens");

    end = run("3314", &last);
    check(end != OPEN, "3 3 1 4 does not open");

    end = run("31t4", &last);
    check(end != OPEN, "3 1 t 4 does not open");

    end = run("314c", &last);
    check(end == LOCKED && last == A_LOCK, "3 1 4 c locks again");
}

static void test_names(void){
    check(strcmp(state_name(GOT2), "GOT2") == 0, "state_name(GOT2) is \"GOT2\"");
    check(strcmp(state_name(N_STATES), "?") == 0, "state_name(N_STATES) is \"?\"");
    check(strcmp(event_name(E_RIGHT), "RIGHT") == 0, "event_name(E_RIGHT) is \"RIGHT\"");
    check(strcmp(event_name(N_EVENTS), "?") == 0, "event_name(N_EVENTS) is \"?\"");
    check(strcmp(action_name(A_UNLOCK), "UNLOCK") == 0, "action_name(A_UNLOCK) is \"UNLOCK\"");
    check(strcmp(action_name(N_ACTIONS), "?") == 0, "action_name(N_ACTIONS) is \"?\"");
}

int main(void){
    test_table();
    test_events();
    test_sequences();
    test_names();

    printf("\n%d passed, %d failed\n", passed, failed);
    return failed ? 1 : 0;
}