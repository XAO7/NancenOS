#ifndef DELAY_H
#define DELAY_H

#include <stdint.h>

void Delay_Init();
void Delay_ms(uint16_t t);
void Delay_us(uint16_t t);

#endif