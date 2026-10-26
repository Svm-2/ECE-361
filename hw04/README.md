Run `make` to build the `events` program.

Run `make test` to build and run the tests. The output should be:
```
./tests/test_tally
PASS: first add returns 1
PASS: second add returns 2
PASS: count matches number of adds
PASS: size counts different names
PASS: name never added has count 0
PASS: empty name is refused
PASS: name of exactly TALLY_LEN chars is accepted
PASS: name of TALLY_LEN + 1 chars is refused
PASS: add with NULL tally returns -1
PASS: add with NULL name returns -1
PASS: count with NULL tally returns 0
PASS: count with NULL name returns 0
PASS: size of NULL returns 0
PASS: destroy(NULL) does nothing
PASS: new name in a full tally is refused
PASS: existing name in a full tally still counts
PASS: TALLY_MAX tallies can be created
PASS: one more than TALLY_MAX returns NULL
PASS: create works again after a destroy
PASS: reused tally starts empty
PASS: two tallies are independent
PASS: print lists names in strcmp order as 'name count'
22 of 22 tests passed
```

To run the program: `./events < data/door.txt`
```
Austin 2
Bob 1
Evan 1
Gabe 1
Henry 1
Lauren 1
names: 6, lines skipped: 2

```

Opaque types are great for hiding details of a data structure from a user by declaring a struct without a body in the header and defining it in the .c file. This type lets the compiler stop callers from reaching inside. When I added `printf("%d\n", t->n);`, the following error was printed in the terminal. When the line was removed, the program compiled and ran as normal. 
```
gcc -std=c11 -Wall -Wextra -I. -c events.c -o events.o
events.c:16:21: error: incomplete definition of type 'tally_t' (aka 'struct tally')
   16 |     printf("%d\n", t->n);
      |                    ~^
./tally.h:9:16: note: forward declaration of 'struct tally'
    9 | typedef struct tally tally_t; /* opaque */
      |                ^
1 error generated.
make: *** [events.o] Error 1
```