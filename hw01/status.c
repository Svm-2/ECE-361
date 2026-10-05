#include "status.h"
#include "bits.h"
#include <stdint.h>
#define HEAT_POS 0
#define HEAT_WIDTH 1
#define COOL_POS 1
#define COOL_WIDTH 1
#define FAN_POS 2
#define FAN_WIDTH 1
#define FAULT_POS 3
#define FAULT_WIDTH 1
#define MODE_POS 4
#define MODE_WIDTH 3
#define RESERVED_POS 7
#define RESERVED_WIDTH 1
#define SETPOINT_POS 8
#define SETPOINT_WIDTH 8

status_t status_unpack(uint16_t word){
    status_t status;
    status.HEAT = get_field(word, HEAT_POS, HEAT_WIDTH);
    status.COOL = get_field(word, COOL_POS, COOL_WIDTH);
    status.FAN = get_field(word, FAN_POS, FAN_WIDTH);
    status.FAULT = get_field(word, FAULT_POS, FAULT_WIDTH);
    status.MODE = get_field(word, MODE_POS, MODE_WIDTH);
    status.SETPOINT = sign_extend(get_field(word, SETPOINT_POS, SETPOINT_WIDTH), SETPOINT_WIDTH);
    status.reserved = get_field(word, RESERVED_POS, RESERVED_WIDTH);
    return status;
}