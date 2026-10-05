#ifndef STATUS_T_H
#define STATUS_T_H
#include <stdint.h>

typedef struct {
    uint8_t HEAT, COOL, FAN, FAULT, reserved;
    uint8_t MODE;
    int8_t SETPOINT;
} status_t;

status_t status_unpack(uint16_t word);

#endif