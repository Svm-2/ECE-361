#!/bin/sh

cd "$(dirname "$0")" || exit 2

if [ ! -x ./balance ]; then
    echo "regress.sh: ./balance not found; run make first" >&2
    exit 2
fi

pass=0
fail=0
tmp=$(mktemp) || exit 2
trap 'rm -f "$tmp"' EXIT

for input in inputs/*.txt; do
    name=$(basename "$input" .txt)
    want_out="expected/$name.out"
    want_status=$(cat "expected/$name.status" 2>/dev/null)

    ./balance < "$input" > "$tmp"
    status=$?

    if cmp -s "$tmp" "$want_out" && [ "$status" = "$want_status" ]; then
        echo "PASS: $name"
        pass=$((pass + 1))
    else
        echo "FAIL: $name"
        echo "    expected (status $want_status): $(cat "$want_out" 2>/dev/null)"
        echo "    got      (status $status): $(cat "$tmp")"
        fail=$((fail + 1))
    fi
done

echo "$pass of $((pass + fail)) regression tests passed"
[ "$fail" -eq 0 ]
