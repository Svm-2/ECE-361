#include "tally.h"

struct entry {
    char name[TALLY_LEN + 1];
    int count;
};

struct tally{
    int n;
    int in_use;
    struct entry entries[TALLY_NAMES];
};

static tally_t pool[TALLY_MAX];

tally_t *tally_create(void){
    for (int i = 0; i < TALLY_MAX; i++){
        if (!pool[i].in_use) {
            pool[i].in_use = 1;
            pool[i].n = 0;
            return &pool[i];
        }
    }
    return NULL; 
}

void tally_destroy(tally_t *t){
    if(t == NULL){
        return;
    }
    t->in_use = 0;
}

int tally_add(tally_t *t, const char *name){
    if(t == NULL || name == NULL || name[0] == '\0' || strlen(name) > TALLY_LEN){
        return -1;
    }

    int i = 0;
    while(i < t->n && strcmp(t->entries[i].name, name) < 0){
        i++;
    }
    if(i < t->n && strcmp(t->entries[i].name, name) == 0){
        return ++t->entries[i].count;
    }
    if(t->n >= TALLY_NAMES){
        return -1;
    }
    for(int j = t->n; j > i; j--){
        t->entries[j] = t->entries[j -1];
    }
    strcpy(t->entries[i].name, name);
    t->entries[i].count = 1;
    t->n++;

    return 1;
}

int tally_count(const tally_t *t, const char *name){
     if(t == NULL || name == NULL){
        return 0;
    }
    
    int i = 0;
    while (i < t->n && strcmp(t->entries[i].name, name) < 0) {
        i++;
    }

    if(i < t->n && strcmp(t->entries[i].name, name) == 0){
        return t->entries[i].count;
    }
    return 0;
}

int tally_size(const tally_t *t){
    if(t == NULL){
        return 0;
    }
    return t->n;
}

void tally_print(const tally_t *t, FILE *out){
    if(t == NULL){
        return;
    }
    for(int i = 0; i < t->n; i++){
        fprintf(out, "%s %d\n", t->entries[i].name, t->entries[i].count);
    }
}
