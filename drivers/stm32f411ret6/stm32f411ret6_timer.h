#ifndef STM32F411RET6_TIMER_H
#define STM32F411RET6_TIMER_H

#include <stdint.h>

void timer_init(uint8_t which);
void timer_set(uint8_t which, uint16_t time_ms);
void timer_start(uint8_t which);
void timer_stop(uint8_t which);
uint8_t timer_reach(uint8_t which);
void timer_reach_clear(uint8_t which);

#endif