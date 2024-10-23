#include <delay.h>
#include <stm32f411ret6_timer.h>

#define TIM_USED 5

void delay_init()
{
    timer_init(TIM_USED);
}

void delay_ms(uint32_t t)
{
    timer_set(TIM_USED, t);
    timer_start(TIM_USED);
    while (!timer_reach(TIM_USED))
        ;
    timer_reach_clear(TIM_USED);
    timer_stop(TIM_USED);
}