#include <stdio.h>
#include <stdint.h>
#include "bits.h"
#include "status.h"

int check(int32_t result, int32_t expected, char *name){
    if(result == expected){
        printf("PASS: %s\n", name);
        return 0;
    }else{
        printf("FAIL: %s\n", name);
        return 1;
    }
}

int ucheck(uint32_t result, uint32_t expected, char *name){
    if(result == expected){
        printf("PASS: %s\n", name);
        return 0;
    }else{
        printf("FAIL: %s\n", name);
        return 1;
    }
}

int main(){
    int failures = 0;

    printf("Testing print_binary(0x2C, 8), expected: 0010 1100\n");
    print_binary(0x2C, 8);
    printf("\n");

    failures += ucheck(get_field(0x1, 0, 1), 1, "get_field width 1");
    failures += ucheck(get_field(0xFFFFFFFF, 0, 32), 0xFFFFFFFF, "get_field width 32");
    failures += ucheck(get_field(0xFFFFFFFF, 31, 1), 1, "get_field pos 31");
    failures += ucheck(get_field(0xFF00, 8, 8), 0xFF, "get_field mid field");

    failures += check(sign_extend(0x80, 8), -128 , "sign_extend negative");
    failures += check(sign_extend(0x1, 1), -1, "sign_extend width 1");
    failures += check(sign_extend(0xFFFFFFFF, 32), -1, "sign_extend width 32");

    failures += ucheck(set_field(0x0F, 1, 1, 0), 0x0D, "set_field width 1");
    failures += ucheck(set_field(0x0F, 0, 32, 0xFFFFFFFF), 0xFFFFFFFF, "set_field width 32");
    failures += ucheck(set_field(0x0F, 31, 1, 0xFFFF), 0x8000000F, "set_field pos 31");
    failures += ucheck(set_field(0xFFFF, 1, 8, 0x00), 0xFE01, "set_field mid field");

    status_t s = status_unpack(0x1631);
failures += check(s.HEAT, 1, "status_unpack 0x1631 HEAT");
failures += check(s.SETPOINT, 22, "status_unpack 0x1631 SETPOINT");
failures += ucheck(s.MODE, 3, "status_unpack 0x1631 MODE");

status_t s2 = status_unpack(0x0000);
failures += check(s2.HEAT, 0, "status_unpack 0x0000 HEAT");
failures += check(s2.SETPOINT, 0, "status_unpack 0x0000 SETPOINT");
failures += ucheck(s2.MODE, 0, "status_unpack 0x0000 MODE");

status_t s3 = status_unpack(0x0011);
failures += check(s3.HEAT, 1, "status_unpack 0x0011 HEAT");
failures += check(s3.SETPOINT, 0, "status_unpack 0x0011 SETPOINT");
failures += ucheck(s3.MODE, 1, "status_unpack 0x0011 MODE");

    printf("%d tests failed\n", failures);
    return failures;
}