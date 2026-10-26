#include <stdio.h>
#include <string.h>
#include "tally.h"
 
#define LINE_MAX_LEN 256
 
int main(void){
    char line[LINE_MAX_LEN];
    int skipped = 0;
 
    tally_t *t = tally_create();
    if (t == NULL) {
        fprintf(stderr, "events: could not create a tally\n");
        return 1;
    }
    
    while (fgets(line, sizeof line, stdin) != NULL) {
        size_t len = strcspn(line, "\n");
 
        if (line[len] == '\n') {
            line[len] = '\0';             
        } else if (!feof(stdin)) {
            int c;
            while ((c = getchar()) != '\n' && c != EOF) {
            }
        }
 
        len = strlen(line);
        if (len > 0 && line[len - 1] == '\r') {
            line[len - 1] = '\0';
        }
 
        if (line[0] == '\0' || line[0] == '#') {
            continue;                   
        }
 
        if (tally_add(t, line) == -1) {
            skipped++;               
        }
    }

    tally_print(t, stdout);
    printf("names: %d, lines skipped: %d\n", tally_size(t), skipped);
 
    tally_destroy(t);
    return 0;
}
