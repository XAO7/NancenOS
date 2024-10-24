#include <stm32f411ret6_timer.h>
#include <stm32f411ret6.h>
#include <tools.h>

void timer_init(Timer_Setting *setting)
{
    int i = setting->Timer;

    // Enable the clock for TIMx
    SET_BIT(RCC->APB1ENR, i, 1);

    timer_set(setting);

    // Enable the update interrupt for TIM2 by setting the bit in the DIER register
    // SET_BIT(TIM2->DIER, 0, 1);

    // Enable the NVIC interrupt for TIM2 (IRQ position 28 in ISER register)
    // SET_BIT(NVIC->ISER[0], 28, 1);
}

void timer_set(Timer_Setting *setting)
{
    int i = setting->Timer;
    TIM_TypeDef *TIMx = (TIM_TypeDef *)(TIM2_BASE + i * 0x400);

    // Set count direction
    SET_BIT(TIMx->CR1, 4, setting->Direction);

    // Set the prescaler (PSC)
    SET_HW_32(TIMx->PSC, 0, setting->PSC);

    SET_HW_32(TIMx->ARR, 0, setting->ARR);
    // stm32f411ret6 TIM5->ARR reset value 0xffff ffff
    SET_HW_32(TIMx->ARR, 1, 0);

    SET_BIT(TIMx->EGR, 0, 1);
    SET_BIT(TIMx->SR, 0, 0);
}

void timer_start(uint8_t which)
{
    TIM_TypeDef *TIMx = (TIM_TypeDef *)(TIM2_BASE + which * 0x400);
    SET_BIT(TIMx->EGR, 0, 1);
    SET_BIT(TIMx->SR, 0, 0);
    SET_BIT(TIMx->CR1, 0, 1);
}

void timer_stop(uint8_t which)
{
    TIM_TypeDef *TIMx = (TIM_TypeDef *)(TIM2_BASE + which * 0x400);
    SET_BIT(TIMx->CR1, 0, 0);
}

uint8_t timer_reach(uint8_t which)
{
    TIM_TypeDef *TIMx = (TIM_TypeDef *)(TIM2_BASE + which * 0x400);
    return (TIMx->SR & 0x1);
}

void timer_reach_clear(uint8_t which)
{
    TIM_TypeDef *TIMx = (TIM_TypeDef *)(TIM2_BASE + which * 0x400);
    SET_BIT(TIMx->SR, 0, 0);
}

uint16_t timer_cur_count(uint8_t which)
{
    TIM_TypeDef *TIMx = (TIM_TypeDef *)(TIM2_BASE + which * 0x400);
    return TIMx->CNT;
}
