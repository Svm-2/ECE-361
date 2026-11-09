#include "scenario.h"
#include "sensor.h"
#include "panel.h"
#include <stdio.h>
#include <stdbool.h>
#include "iom361_r4.h"

int main(int argc, char *argv[]){
    static scenario_t s;
    int rc;
    if(argc < 2){
        return -1;
    }
    int result = scenario_load(argv[1], &s);
    if(result != 0){
        return -1;
    }

    uint32_t* base = iom361_initialize(4,4, &rc);
    if(base == NULL)
        return -1;
    
    iom361_set_display(false); 


    int last_tick = s.lines[s.count - 1].tick;
    uint32_t before = 0;
 
    for(int tick = 0; tick <= last_tick; tick++){
        const scenario_line_t* line = line_in_force(&s, tick);
        if(line == NULL)
            continue;
        _iom361_set_sensor1(line->temp, line->rh);
        _iom361_set_switches(line->switches);
 
        time_t now = s.start + tick;
 
        reading_t r;
        rc = sensor_read(base, now, &r);
        if(rc != 0)
            return -1;
 
        uint32_t switches = iom361_readReg(base, SWITCHES_REG, &rc);
        if(rc != 0)
            return -1;
 
        uint32_t pressed = panel_pressed(switches, before);
        for(int k = 0; k < 4; k++){
            if(pressed & (1u << k)){
                if(panel_toggle(base, k) != 0)
                    return -1;
            }
        }
 
        uint32_t leds = iom361_readReg(base, LEDS_REG, &rc);
        if(rc != 0)
            return -1;
 
        char when[32];
        struct tm* utc = gmtime(&r.t);
        if(utc == NULL)
            return -1;
        strftime(when, sizeof(when), "%Y-%m-%d %H:%M:%S", utc);
 
        printf("%s temp=%.1f rh=%.1f switches=0x%X pressed=0x%X leds=0x%X\n",
               when, r.temp_c, r.rh_pct, (unsigned) switches, (unsigned) pressed, (unsigned) leds);
 
        before = switches;
    }
    return 0;
}