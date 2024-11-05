#include <stm32f411ret6.h>
#include <stm32f411ret6_init.h>
#include <arm_cm4.h>
#include <tools.h>

void __MCU_Init()
{
    // __MCO2_Out();
    __SYSCLK_Init();
}

// SYSLCK = HCLK = 100MHz
void __SYSCLK_Init()
{
    // // enable fault handlers (mem bus usage)
    SET_BYTE(SCB->SHCSR, 2, 0x07);

    // // enable NONBASETHRDENA !!!
    // SET_BIT_32(SCB->CCR, 0, 1);

    // HSE ON (bit 16)
    SET_BIT(RCC->CR, 16, 1);

    // Wait until HSE is ready (bit 17)
    while (!(RCC->CR & (1 << 17)))
        ;

    // Caution: Needs HW or W access
    SET_BYTE_32(RCC->PLLCFGR, 0, 0x10); // Sets PLLM = 16
    SET_BYTE_32(RCC->PLLCFGR, 1, 0x20); // Sets PLLN = 128
    SET_BYTE_32(RCC->PLLCFGR, 2, 0x40); // Sets PLLP = 2 and PLLSRC = HSE

    // PLL ON (bit 24)
    SET_BIT(RCC->CR, 24, 1);

    // Wait until PLL is ready (bit 25)
    while (!(RCC->CR & (1 << 25)))
        ;

    // APB2 Prescaler (/2) and APB1 Prescaler (/4)
    SET_BYTE(RCC->CFGR, 1, 0x94);

    // Set 3 wait states
    SET_BYTE_32(FLASH->ACR, 0, 0x03);

    // Switch system clock (SW) to PLL (bits [1:0] = 10)
    SET_BYTE(RCC->CFGR, 0, 0x02);

    // Wait until PLL is used as the system clock (bits [3:2] = 10)
    while ((RCC->CFGR & (0x0C)) != 0x08)
        ;

    // enable instruction cache, data cache, and prefetch buffer
    SET_BYTE_32(FLASH->ACR, 1, 0x07);
}

void __MCO2_Out()
{
    // Set SYSCLK out and prescale by 5
    SET_BIT(RCC->CFGR, 27, 1);
    SET_BIT(RCC->CFGR, 28, 1);
    SET_BIT(RCC->CFGR, 29, 1);

    // Enable the clock for GPIOC
    SET_BIT(RCC->AHB1ENR, 2, 1);

    // Set up GPIO stuff
    SET_BIT_32(GPIOC->MODER, 19, 1);
    SET_BIT_32(GPIOC->OSPEEDR, 18, 1);
    SET_BIT_32(GPIOC->OSPEEDR, 19, 1);
}
