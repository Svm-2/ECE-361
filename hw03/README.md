To build this program, run "make test" and the following results will be shown
```
./tests/test_ptr
PASS  swap_float exchanges two values
PASS  swap_float with the same pointer twice
PASS  minmax on several values
PASS  minmax on one value
PASS  minmax with n = 0 returns -1, outputs unchanged
PASS  minmax with a = NULL returns -1, outputs unchanged
PASS  minmax with min = NULL returns -1, max unchanged
PASS  minmax with max = NULL returns -1, min unchanged
PASS  find_above with two matches returns the first
PASS  find_above with no match returns NULL
PASS  find_above skips a value equal to the threshold
PASS  find_above with only equal values returns NULL
PASS  reverse on an even length
PASS  reverse on an odd length
PASS  reverse with n = 1 does nothing
PASS  reverse with a = NULL does nothing

16 passed, 0 failed, 16 total
```