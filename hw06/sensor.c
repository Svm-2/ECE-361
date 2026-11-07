#include "sensor.h"
#include <math.h>
#define MASK 0xFFFFFu

int sensor_read(uint32_t *base, time_t now, reading_t *r){
    int rc;
    uint32_t raw_temp = iom361_readReg(base, TEMP_REG, &rc);
    if(rc != 0)
        return rc;

    uint32_t raw_hmd = iom361_readReg(base, HUMID_REG, &rc);
    if(rc != 0)
        return rc;

    raw_temp &= MASK;
    raw_hmd &= MASK;

    double temp = raw_temp / 1048576.0 * 200.0 - 50.0;
    double hmd = raw_hmd / 1048576.0 * 100.0;

    long temp10 = lround(temp * 10.0);
    long hmd10 = lround(hmd * 10.0);

    r->temp_c = temp10 / 10.0f;
    r->rh_pct = hmd10 / 10.0f;
    r->t = now;

    return 0;
}