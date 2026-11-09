#ifndef SENSOR_H
#define SENSOR_H
#include <stdint.h>
#include "iom361_r4.h"
#include <time.h>

/*A function that reads the temperature and humidity registers and converts them with the formulas in the register table above, 
rounded to 0.1 °C and 0.1 %RH. Return the reading through a pointer and report failure through the return value. */ 
typedef struct{time_t t; float temp_c; float rh_pct;} reading_t;

#endif /* SENSOR_H */