#include <stdio.h>
#include <stdlib.h>

#include "istack.h"

static int closer_for(int open)
{
    switch (open) {
    case '(': return ')';
    case '[': return ']';
    case '{': return '}';
    default:  return '?';
    }
}

int main(void)
{
    istack_t *s = istack_create();
    if (s == NULL) {
        fprintf(stderr, "balance: out of memory\n");
        return 2;
    }

    unsigned long line = 1, col = 0;
    size_t pairs = 0, deepest = 0;
    int status = 0;
    int c;

    while ((c = getchar()) != EOF) {
        col++;

        if (c == '(' || c == '[' || c == '{') {
            if (istack_push(s, c) != 0) {
                fprintf(stderr, "balance: out of memory\n");
                status = 2;
                break;
            }
            if (istack_count(s) > deepest)
                deepest = istack_count(s);
        } else if (c == ')' || c == ']' || c == '}') {
            int open;
            if (istack_pop(s, &open) != 0) {
                printf("line %lu, column %lu: found '%c', nothing open\n",
                       line, col, c);
                status = 1;
                break;
            }
            if (closer_for(open) != c) {
                printf("line %lu, column %lu: found '%c', expected '%c'\n",
                       line, col, c, closer_for(open));
                status = 1;
                break;
            }
            pairs++;
        } else if (c == '\n') {
            line++;
            col = 0;
        }
    }

    if (status == 0) {
        if (istack_is_empty(s)) {
            printf("balanced: %zu pairs, deepest %zu\n", pairs, deepest);
        } else {
            int innermost = '?';
            istack_peek(s, &innermost);
            printf("end of input: %zu still open, innermost '%c'\n",
                   istack_count(s), innermost);
            status = 1;
        }
    }

    istack_destroy(s);
    return status;
}
