#include <stdio.h>
#include "reading.h"

int reading_read(int ticks[], float temps[], float hums[], int *skipped){
    char line[LINE_LEN];
    int count = 0;
    *skipped = 0;

    while (fgets(line, sizeof line, stdin) != NULL) {
        int i = 0;
        while (line[i] == ' ' || line[i] == '\t')
            i++;
        if (line[i] == '\n' || line[i] == '\0' || line[i] == '#')
            continue;
        if (count == MAX_READINGS) {
            fprintf(stderr, "warning: more than %d readings, the rest are ignored\n", MAX_READINGS);
            break;
        }
        if (sscanf(line, "%d %f %f", &ticks[count], &temps[count], &hums[count]) == 3)
            count++;
        else
            (*skipped)++;
    }

    return count;
}