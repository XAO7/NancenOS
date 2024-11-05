#include <stm32f411ret6_gpio.h>
#include <stm32f411ret6.h>
#include <tools.h>

void GPIO_Init(GPIO_Setting *setting)
{
    // Enable port clock
    SET_BIT_32(RCC->AHB1ENR, setting->port, 1);

    GPIO_Set(setting);
}

void GPIO_Set(GPIO_Setting *setting)
{
    GPIO_TypeDef *GPIOx = (GPIO_TypeDef *)(GPIOA_BASE + 0x400 * setting->port);
    if (setting->port == GPIO_H)
        GPIOx = GPIOH;

    uint8_t num = setting->num;

    // Set Mode
    SET_BIT_32(GPIOx->MODER, num * 2, setting->mode & 0x1);
    SET_BIT_32(GPIOx->MODER, num * 2 + 1, setting->mode & 0x2);

    // Set Output Type
    SET_BIT_32(GPIOx->OTYPER, num, setting->outputType);

    // Set Output Speed
    SET_BIT_32(GPIOx->OSPEEDR, num * 2, setting->outputSpeed & 0x1);
    SET_BIT_32(GPIOx->OSPEEDR, num * 2 + 1, setting->outputSpeed & 0x2);
}
