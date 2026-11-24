/*An enum for the 5 states and an enum for events. A transition table: an array, indexed by state and event, 
that gives the next state and the action.*/
#ifndef FSM_H
#define FSM_H

typedef enum { IDLE, HANDSHAKE, CHARGING, THROTTLED, FAULT, N_STATES } state_t;

typedef enum {
    EV_UNPLUG, EV_PLUG, EV_TEMP_CRIT, EV_HS_TIMEOUT,
    EV_CAR_READY_ON, EV_CAR_READY_OFF,
    EV_STOP, EV_START, EV_START_EARLY,
    EV_TEMP_HIGH, EV_TEMP_NORMAL,
    N_EVENTS
} event_t;

typedef enum { A_UNDEFINED, A_NONE, A_START_TIMER, A_STOP_TIMER, A_RESET, N_ACTIONS } action_t;

typedef struct { state_t next; action_t action; } transition_t;

extern const transition_t fsm_table[N_STATES][N_EVENTS];

state_t fsm_step(state_t s, event_t e, action_t *action);
const char *state_name(state_t s);
const char *event_name(event_t e);
const char *action_name(action_t a);

#endif