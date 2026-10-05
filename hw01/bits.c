#include "bits.h"

void print_binary(uint32_t x, int width){
    for(int i=width-1; i >= 0; i--){
        printf("%d", (x >> i) & 1);
        if(i % 4 == 0 && i != 0)
            printf(" ");
    }
}

uint32_t get_field(uint32_t word, int pos, int width){
    uint32_t mask = (width == 32) ? 0xFFFFFFFF : (1u << width) - 1;
    return (word >> pos) & mask;
}

uint32_t set_field(uint32_t word, int pos, int width, uint32_t value){
    uint32_t mask = (width == 32) ? 0xFFFFFFFF : (1u << width) - 1;
    return (word & ~(mask << pos)) | ((value & mask) << pos);
}

int32_t sign_extend(uint32_t value, int width){
    if((value >> (width -1)) & 1){
        return ~((1 << width)-1) | value;
    }
    else{
        return value & ((1 << width)-1);
    }
}