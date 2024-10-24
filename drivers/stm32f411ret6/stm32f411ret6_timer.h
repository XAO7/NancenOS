#ifndef STM32F411RET6_TIMER_H
#define STM32F411RET6_TIMER_H

#include <stdint.h>

typedef enum ENUM_Timer
{
    Timer_2 = 0,
    Timer_3 = 1,
    Timer_4 = 2,
    Timer_5 = 3,
} ENUM_Timer;

typedef enum ENUM_Timer_Direction
{
    Timer_Direction_Up = 0,
    Timer_Direction_Down = 1,
} ENUM_Timer_Direction;

typedef struct Timer_Setting
{
    uint8_t Timer;
    uint8_t Direction;
    uint16_t PSC;
    uint16_t ARR;
} Timer_Setting;

void timer_init(Timer_Setting *setting);
void timer_set(Timer_Setting *setting);
void timer_start(uint8_t which);
void timer_stop(uint8_t which);
uint8_t timer_reach(uint8_t which);
void timer_reach_clear(uint8_t which);
uint16_t timer_cur_count(uint8_t which);



#endif