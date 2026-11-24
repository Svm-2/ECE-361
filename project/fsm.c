#include <stddef.h>
#include "fsm.h"

const transition_t fsm_table[N_STATES][N_EVENTS] = {
    [IDLE] = {
        [EV_UNPLUG]        = {IDLE,      A_RESET},
        [EV_PLUG]          = {HANDSHAKE, A_START_TIMER},
        [EV_TEMP_CRIT]     = {IDLE,      A_NONE},
        [EV_HS_TIMEOUT]    = {IDLE,      A_NONE},
        [EV_CAR_READY_ON]  = {IDLE,      A_NONE},
        [EV_CAR_READY_OFF] = {IDLE,      A_NONE},
        [EV_STOP]          = {IDLE,      A_NONE},
        [EV_START]         = {IDLE,      A_NONE},
        [EV_START_EARLY]   = {IDLE,      A_NONE},
        [EV_TEMP_HIGH]     = {IDLE,      A_NONE},
        [EV_TEMP_NORMAL]   = {IDLE,      A_NONE},
    },
    [HANDSHAKE] = {
        [EV_UNPLUG]        = {IDLE,      A_RESET},
        [EV_PLUG]          = {HANDSHAKE, A_NONE},
        [EV_TEMP_CRIT]     = {FAULT,     A_RESET},
        [EV_HS_TIMEOUT]    = {FAULT,     A_RESET},
        [EV_CAR_READY_ON]  = {HANDSHAKE, A_STOP_TIMER},
        [EV_CAR_READY_OFF] = {HANDSHAKE, A_START_TIMER},
        [EV_STOP]          = {HANDSHAKE, A_NONE},
        [EV_START]         = {CHARGING,  A_NONE},
        [EV_START_EARLY]   = {HANDSHAKE, A_NONE},
        [EV_TEMP_HIGH]     = {HANDSHAKE, A_NONE},   
        [EV_TEMP_NORMAL]   = {HANDSHAKE, A_NONE},
    },
    [CHARGING] = {
        [EV_UNPLUG]        = {IDLE,      A_RESET},
        [EV_PLUG]          = {CHARGING,  A_NONE},
        [EV_TEMP_CRIT]     = {FAULT,     A_RESET},
        [EV_HS_TIMEOUT]    = {CHARGING,  A_NONE}, 
        [EV_CAR_READY_ON]  = {CHARGING,  A_NONE},
        [EV_CAR_READY_OFF] = {HANDSHAKE, A_START_TIMER},
        [EV_STOP]          = {HANDSHAKE, A_NONE},
        [EV_START]         = {CHARGING,  A_NONE},
        [EV_START_EARLY]   = {CHARGING,  A_NONE},
        [EV_TEMP_HIGH]     = {THROTTLED, A_NONE},
        [EV_TEMP_NORMAL]   = {CHARGING,  A_NONE},
    },
    [THROTTLED] = {
        [EV_UNPLUG]        = {IDLE,      A_RESET},
        [EV_PLUG]          = {THROTTLED, A_NONE},
        [EV_TEMP_CRIT]     = {FAULT,     A_RESET}, 
        [EV_HS_TIMEOUT]    = {THROTTLED, A_NONE},
        [EV_CAR_READY_ON]  = {THROTTLED, A_NONE},
        [EV_CAR_READY_OFF] = {HANDSHAKE, A_START_TIMER},
        [EV_STOP]          = {HANDSHAKE, A_NONE},
        [EV_START]         = {THROTTLED, A_NONE},
        [EV_START_EARLY]   = {THROTTLED, A_NONE},
        [EV_TEMP_HIGH]     = {THROTTLED, A_NONE},
        [EV_TEMP_NORMAL]   = {CHARGING,  A_NONE},
    },
    [FAULT] = {
        [EV_UNPLUG]        = {IDLE,      A_RESET},
        [EV_PLUG]          = {FAULT,     A_NONE},
        [EV_TEMP_CRIT]     = {FAULT,     A_NONE}, 
        [EV_HS_TIMEOUT]    = {FAULT,     A_NONE},
        [EV_CAR_READY_ON]  = {FAULT,     A_NONE},
        [EV_CAR_READY_OFF] = {FAULT,     A_NONE},
        [EV_STOP]          = {FAULT,     A_NONE},
        [EV_START]         = {FAULT,     A_NONE},
        [EV_START_EARLY]   = {FAULT,     A_NONE},
        [EV_TEMP_HIGH]     = {FAULT,     A_NONE},
        [EV_TEMP_NORMAL]   = {FAULT,     A_NONE},
    }
};

state_t fsm_step(state_t s, event_t e, action_t *action) {
    if ((int)s < 0 || s >= N_STATES || (int)e < 0 || e >= N_EVENTS) {
        if (action != NULL) {
            *action = A_NONE;
        }
        return s;
    }

    const transition_t t = fsm_table[s][e];

    if (action != NULL) {
        *action = t.action;
    }
    return t.next;
}

static const char *const state_names[N_STATES] = {
    [IDLE]      = "IDLE",
    [HANDSHAKE] = "HANDSHAKE",
    [CHARGING]  = "CHARGING",
    [THROTTLED] = "THROTTLED",
    [FAULT]     = "FAULT"
};

static const char *const event_names[N_EVENTS] = {
    [EV_UNPLUG]        = "UNPLUG",
    [EV_PLUG]          = "PLUG",
    [EV_TEMP_CRIT]     = "TEMP_CRIT",
    [EV_HS_TIMEOUT]    = "HS_TIMEOUT",
    [EV_CAR_READY_ON]  = "CAR_READY_ON",
    [EV_CAR_READY_OFF] = "CAR_READY_OFF",
    [EV_STOP]          = "STOP",
    [EV_START]         = "START",
    [EV_START_EARLY]   = "START_EARLY",
    [EV_TEMP_HIGH]     = "TEMP_HIGH",
    [EV_TEMP_NORMAL]   = "TEMP_NORMAL"
};

static const char *const action_names[N_ACTIONS] = {
    [A_UNDEFINED]   = "UNDEFINED",
    [A_NONE]        = "NONE",
    [A_START_TIMER] = "START_TIMER",
    [A_STOP_TIMER]  = "STOP_TIMER",
    [A_RESET]       = "RESET"
};

const char *state_name(state_t s) {
    if ((int)s < 0 || s >= N_STATES) {
        return "?";
    }
    return state_names[s];
}

const char *event_name(event_t e) {
    if ((int)e < 0 || e >= N_EVENTS) {
        return "?";
    }
    return event_names[e];
}

const char *action_name(action_t a) {
    if ((int)a < 0 || a >= N_ACTIONS) {
        return "?";
    }
    return action_names[a];
}