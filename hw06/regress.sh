#!/bin/sh
pass=0
fail=0
for scenario in scenarios/*.txt; do
    name=$(basename "$scenario")
    if ./replay "$scenario" | diff - "expected/$name" > /dev/null; then
        echo "PASS $name"
        pass=$((pass + 1))
    else
        echo "FAIL $name"
        fail=$((fail + 1))
    fi
done
echo "$pass passed, $fail failed"
[ "$fail" -eq 0 ]
