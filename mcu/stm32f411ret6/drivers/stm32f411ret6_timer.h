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
    uint8_t timer;
    uint8_t direction;
    uint16_t PSC;
    uint16_t ARR;
} Timer_Setting;

void Timer_Init(Timer_Setting *setting);
void Timer_Set(Timer_Setting *setting);
void Timer_Start(uint8_t which);
void Timer_Stop(uint8_t which);
uint8_t Timer_Reach(uint8_t which);
void Timer_ReachClear(uint8_t which);
uint16_t Timer_CurCount(uint8_t which);



#endif