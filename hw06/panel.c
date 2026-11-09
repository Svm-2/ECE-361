#include "panel.h"
#include "iom361_r4.h"

uint32_t panel_pressed(uint32_t now,uint32_t before){
    return (now & (~before));
}

uint32_t panel_released(uint32_t now, uint32_t before){
    return (before & (~now));
}

int panel_led(uint32_t *base, int n, int on){
    int rc; 
    if(n > 31 || n < 0)
        return -1;
        
    uint32_t leds = iom361_readReg(base, LEDS_REG, &rc); 
    if(rc != 0)
        return rc;
    if(on == 0)
        leds &= ~(1u << n);
    else
        leds |= 1u << n;

    iom361_writeReg(base, LEDS_REG, leds, &rc); 

    return rc;
}

int panel_toggle(uint32_t *base, int n){
    int rc;
    if(n > 31 || n < 0)
        return -1;
        
    uint32_t leds = iom361_readReg(base, LEDS_REG, &rc); 
    if(rc != 0)
        return rc;
    leds ^= 1u << n;

    iom361_writeReg(base, LEDS_REG, leds, &rc); 

    return rc;
}