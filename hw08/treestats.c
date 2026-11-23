#include "bst.h"
#include <stdio.h>

int main(void)
{
    bst_t *t = bst_create();
    size_t count = 0;
    int value;
    int status;

    if (t == NULL) {
        fprintf(stderr, "out of memory\n");
        return 1;
    }

    while ((status = scanf("%d", &value)) == 1) {
        if (bst_insert(t, value) != 0) {
            fprintf(stderr, "out of memory\n");
            bst_destroy(t);
            return 1;
        }
        count++;
    }

    if (status == 0) {
        printf("not a number after %zu values\n", count);
        bst_destroy(t);
        return 1;
    }

    if (count == 0) {
        printf("empty tree\n");
    } else {
        printf("n %zu, height %zu\n", bst_size(t), bst_height(t));
    }
    bst_destroy(t);
    return 0;
}