#include <frypi.h>
#include <stm32f411ret6.h>
#include <tools.h>

void led_init()
{
    // Enable the clock for GPIOC
    SET_BIT(RCC->AHB1ENR, 2, 1);

    SET_BIT_32(GPIOC->MODER, 26, 1);
}

void led_on(uint8_t b)
{
    SET_BIT_32(GPIOC->ODR, 13, (b ? 1 : 0));
}