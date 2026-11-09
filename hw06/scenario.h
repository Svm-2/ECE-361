#ifndef SCENARIO_H
#define SCENARIO_H
#define MAX_LINES 1000
#include <stdint.h>
#include <time.h>

typedef struct{int tick; float temp; float rh; uint32_t switches;} scenario_line_t;
typedef struct{time_t start; scenario_line_t lines[MAX_LINES]; int count;} scenario_t;
int scenario_load(const char* path, scenario_t* s);
const scenario_line_t* line_in_force(const scenario_t* s, int tick);
#endif