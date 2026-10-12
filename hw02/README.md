This assignment was about modulating a large program with multiple functions hosted within one file. Utilizing header files, I split up the functions and tasks in readings.c into histogram.c, stats.c, reading.c, and wrote test functions to validate the output from these tasks. 

To build this project, run make clean, and run make test. After running make test, you should find the following results:
    ./test_stats
    PASS  stats_max one value
    PASS  stats_max three values at start of array
    PASS  stats_max three values at end of array
    PASS  threshold exact value ends run
    PASS  stats_max of 10,000 values
    ALL TESTS PASSED
    sh regress.sh
    PASS  regression edge.txt
    PASS  regression empty.txt
    PASS  regression normal.txt
    PASS  regression edge.txt, threshold 25

