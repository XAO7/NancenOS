#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

void delay_init();
void delay_ms(uint32_t t);
void delay_us(uint32_t t);

#endif