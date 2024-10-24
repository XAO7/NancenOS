#include <delay.h>
#include <stm32f411ret6_timer.h>

void delay_init()
{
    Timer_Setting setting =
        {
            .Timer = Timer_4,
            .Direction = Timer_Direction_Down,
            .PSC = 50 * 1000 - 1,
            .ARR = 0xffff,
        };
    timer_init(&setting);

    setting.Timer = Timer_5;
    setting.PSC = 50 - 1;

    timer_init(&setting);

    timer_start(Timer_4);
    timer_start(Timer_5);
}

void delay_ms(uint16_t t)
{
    uint16_t cur_count = timer_cur_count(Timer_4);
    uint16_t target_count = cur_count - t;
    while (timer_cur_count(Timer_4) != target_count)
        ;
}

void delay_us(uint16_t t)
{
    uint16_t cur_count = timer_cur_count(Timer_5);
    uint16_t target_count = cur_count - t;
    while (timer_cur_count(Timer_5) != target_count)
        ;
}