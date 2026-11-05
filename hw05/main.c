#include "lock.h"
#include <stdio.h>

int main(){
    state_t s = LOCKED; 
    action_t a;

    int c; 
    while((c = getchar()) != EOF){
        int e = lock_event(s, c);
        if (e != -1) {
            state_t next = lock_step(s, (event_t)e, &a);
            printf("%s %c %s -> %s %s\n", state_name(s), c, event_name(e), state_name(next), action_name(a));
            s = next;
        }
    }
    printf("final: %s\n",state_name(s));
    return 0;   
}