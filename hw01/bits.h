/* bits.h contains function declarations for use in bits.c */
#ifndef BITS_H
#define BITS_H
#include <stdint.h>

/*Prints the lowest width bits of x, most signif bit first, in groups of four seperated by a space. print_binary(0x2C, 8) prints 0010 110.*/
void print_binary(uint32_t word, int pos, int width);

/*Returns bits pos to pos+width-1 of word, shifted down to bit 0.*/
uint32_t get_field(uint32_t word, int pos, int width);

/*Returns word with bits pos to pos+width-1 replaced by the lowest width bits of value. All other bits are unmodified*/
uint32_t set_field(uint32_t word, int pos, int width, uint32_t value);

/*Interprets lowest width of bits of value as a two's compliment number and returns as an int32_t.*/
int32_t sign_extend(uint32_t value, int width);

