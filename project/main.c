#include "fsm.h"
#include "iom361_r4.h"
#include "sensor.h"
#include <stdio.h>
#include <stdint.h>

int main(int argc, char *argv[]){
    (void)argc;
    (void)argv;
    int rc;
    uint32_t *base = iom361_initialize(4, 3, &rc);

    if (base == NULL) {
    fprintf(stderr, "iom361_initialize failed: %d\n", rc);
    return 1;
    }

    printf("EV Charging Station\n");
    return 0;
}