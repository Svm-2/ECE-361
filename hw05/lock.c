#include <ctype.h>
#include <stddef.h>
#include "lock.h"

static const char code[] = "314";
_Static_assert(sizeof code - 1 == OPEN, "code length must match the number of digit states");

const transition_t lock_table[N_STATES][N_EVENTS] = {
    [LOCKED] = {
        [E_WRONG] = {LOCKED, A_BEEP},
        [E_RIGHT] = {GOT1, A_NONE},
        [E_CLOSE] = {LOCKED, A_NONE},
        [E_TIMEOUT] = {LOCKED, A_NONE}
    },
    [GOT1] = {
        [E_WRONG] = {LOCKED, A_BEEP},
        [E_RIGHT] = {GOT2, A_NONE},
        [E_CLOSE] = {GOT1, A_NONE},
        [E_TIMEOUT] = {LOCKED, A_NONE},
    },
    [GOT2] = {
        [E_WRONG] = {LOCKED, A_BEEP},
        [E_RIGHT] = {OPEN, A_UNLOCK},
        [E_CLOSE] = {GOT2, A_NONE},
        [E_TIMEOUT] = {LOCKED, A_NONE},
    },
    [OPEN] = {
        [E_WRONG] = {OPEN, A_NONE},
        [E_RIGHT] = {OPEN, A_NONE},
        [E_CLOSE] = {LOCKED, A_LOCK},
        [E_TIMEOUT] = {LOCKED, A_LOCK},
    }
};

state_t lock_step(state_t s, event_t e, action_t *action){
    const transition_t t = lock_table[s][e];

    if(action != NULL){
        *action = t.action;
    }
    return t.next;
}

int lock_event(state_t s, char c){
    switch(c){
        case 'c':
            return E_CLOSE;
        case 't':
            return E_TIMEOUT;
        default:
            if(isdigit(c)){
                if(c == code[s]){
                    return E_RIGHT;
            }
            else{
                return E_WRONG;
            }
        }
        else{
            return -1;
        }
    }
}

static const char *const state_names[N_STATES] = {
    [LOCKED] = "LOCKED",
    [OPEN] = "OPEN",
    [GOT1] = "GOT1",
    [GOT2] = "GOT2"
};

static const char *const event_names[N_EVENTS] = {
    [E_RIGHT] = "RIGHT",
    [E_WRONG] = "WRONG",
    [E_CLOSE] = "CLOSE",
    [E_TIMEOUT] = "TIMEOUT"
};

static const char *const action_names[N_ACTIONS] = {
    [A_UNLOCK] = "UNLOCK",
    [A_LOCK] = "LOCK",
    [A_NONE] = "NONE",
    [A_BEEP] = "BEEP",
    [A_UNDEFINED] = "UNDEFINED"
};

const char *state_name(state_t s){
    if(s >= N_STATES || (int)s < 0){
        return "?";
    }
    return state_names[s];
}

const char *action_name(action_t a){
    if(a >= N_ACTIONS || (int)a < 0){
        return "?";
    }
    return action_names[a];
}

const char *event_name(event_t e){
    if(e >= N_EVENTS || (int)e < 0){
        return "?";
    }
    return event_names[e];
}