Run `make` to build the `events` program.

Run `make test` to build and run the tests. The output should be:
```
PASS: LOCKED + RIGHT -> GOT1 NONE
PASS: LOCKED + WRONG -> LOCKED BEEP
PASS: LOCKED + CLOSE -> LOCKED NONE
PASS: LOCKED + TIMEOUT -> LOCKED NONE
PASS: GOT1 + RIGHT -> GOT2 NONE
PASS: GOT1 + WRONG -> LOCKED BEEP
PASS: GOT1 + CLOSE -> GOT1 NONE
PASS: GOT1 + TIMEOUT -> LOCKED NONE
PASS: GOT2 + RIGHT -> OPEN UNLOCK
PASS: GOT2 + WRONG -> LOCKED BEEP
PASS: GOT2 + CLOSE -> GOT2 NONE
PASS: GOT2 + TIMEOUT -> LOCKED NONE
PASS: OPEN + RIGHT -> OPEN NONE
PASS: OPEN + WRONG -> OPEN NONE
PASS: OPEN + CLOSE -> LOCKED LOCK
PASS: OPEN + TIMEOUT -> LOCKED LOCK
PASS: lock_event(LOCKED, '3') == RIGHT
PASS: lock_event(LOCKED, '5') == WRONG
PASS: lock_event(GOT1, '1') == RIGHT
PASS: lock_event(GOT1, '3') == WRONG
PASS: lock_event(GOT2, '4') == RIGHT
PASS: lock_event(GOT2, '1') == WRONG
PASS: lock_event(OPEN, '3') == WRONG
PASS: lock_event(OPEN, '0') == WRONG
PASS: lock_event(LOCKED, 'c') == CLOSE
PASS: lock_event(GOT1, 'c') == CLOSE
PASS: lock_event(OPEN, 'c') == CLOSE
PASS: lock_event(LOCKED, 't') == TIMEOUT
PASS: lock_event(GOT2, 't') == TIMEOUT
PASS: lock_event(OPEN, 't') == TIMEOUT
PASS: lock_event(LOCKED, 'x') == -1
PASS: lock_event(GOT1, ' ') == -1
PASS: lock_event(OPEN, '\n') == -1
PASS: 3 1 4 opens
PASS: 3 3 1 4 does not open
PASS: 3 1 t 4 does not open
PASS: 3 1 4 c locks again
PASS: state_name(GOT2) is "GOT2"
PASS: state_name(N_STATES) is "?"
PASS: event_name(E_RIGHT) is "RIGHT"
PASS: event_name(N_EVENTS) is "?"
PASS: action_name(A_UNLOCK) is "UNLOCK"
PASS: action_name(N_ACTIONS) is "?"

43 passed, 0 failed
```
To run the program: `./lock < data/codes.txt`
```
LOCKED 3 RIGHT -> GOT1 NONE
GOT1 3 WRONG -> LOCKED BEEP
LOCKED 1 WRONG -> LOCKED BEEP
LOCKED 4 WRONG -> LOCKED BEEP
LOCKED 3 RIGHT -> GOT1 NONE
GOT1 1 RIGHT -> GOT2 NONE
GOT2 t TIMEOUT -> LOCKED NONE
LOCKED 4 WRONG -> LOCKED BEEP
LOCKED 3 RIGHT -> GOT1 NONE
GOT1 1 RIGHT -> GOT2 NONE
GOT2 4 RIGHT -> OPEN UNLOCK
OPEN c CLOSE -> LOCKED LOCK
LOCKED 3 RIGHT -> GOT1 NONE
GOT1 2 WRONG -> LOCKED BEEP
LOCKED 1 WRONG -> LOCKED BEEP
LOCKED 7 WRONG -> LOCKED BEEP
LOCKED 5 WRONG -> LOCKED BEEP
LOCKED 8 WRONG -> LOCKED BEEP
LOCKED 3 RIGHT -> GOT1 NONE
final: GOT1
```