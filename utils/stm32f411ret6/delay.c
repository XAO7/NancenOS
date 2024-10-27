#include <delay.h>
#include <stm32f411ret6_timer.h>

void Delay_Init()
{
    Timer_Setting setting =
        {
            .timer = Timer_4,
            .direction = Timer_Direction_Down,
            .PSC = 50 * 1000 - 1,
            .ARR = 0xffff,
        };
    Timer_Init(&setting);

    setting.timer = Timer_5;
    setting.PSC = 50 - 1;

    Timer_Init(&setting);

    Timer_Start(Timer_4);
    Timer_Start(Timer_5);
}

void Delay_ms(uint16_t t)
{
    uint16_t cur_count = Timer_CurCount(Timer_4);
    uint16_t target_count = cur_count - t;
    while (Timer_CurCount(Timer_4) != target_count)
        ;
}

void Delay_us(uint16_t t)
{
    uint16_t cur_count = Timer_CurCount(Timer_5);
    uint16_t target_count = cur_count - t;
    while (Timer_CurCount(Timer_5) != target_count)
        ;
}