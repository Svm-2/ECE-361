Run `make` to build the program.

Run `make test` to build and run the tests. The output should be:
```
PASS: NULL tree: size 0
PASS: NULL tree: height 0
PASS: NULL tree: insert returns -1
PASS: NULL tree: not found, 0 visits
PASS: NULL tree: destroy does nothing
PASS: seven keys: tree built
PASS: seven keys: size 7
PASS: seven keys: height 3
PASS: seven keys: 31 found in 3 visits
PASS: seven keys: 15 not found in 3 visits
PASS: seven keys: 31 found with visits NULL
PASS: duplicate: tree built
PASS: duplicate: kept, size 2
PASS: increasing: tree built
PASS: increasing: height equals number of keys
PASS: destroy full tree: tree built
PASS: destroy full tree: returned (memcheck checks for leaks)
PASS: empty tree: tree created
PASS: empty tree: search finds nothing, 0 visits
ALL PASS: 0 failure(s)
```

When using the orignal search function we got the following error from memcheck:
```
bst.c:105:20: runtime error: member access within null pointer of type 'struct node'
```
