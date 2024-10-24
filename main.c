#include <stm32f411ret6_init.h>
#include <stm32f411ret6_usart.h>
#include <delay.h>
#include <frypi.h>

// void task0()
// {
//     while (1)
//     {
//         usart_sendline("task0");
//     }
// }

void main()
{
    // SET_BIT_32(RCC->APB2ENR, 2, 1);
    // SET_BYTE_32(GPIOA->CRL, 0, 0x01);

    // task_set(0, task0);

    // usart_sendline("main...");
    // usart_sendline("main...");
    // usart_sendline("main...");

    mcu_init();

    usart_init();
    led_init();
    delay_init();

    while (1)
    {
        usart_sendline("Hello from FryPi");
        // usart_sendbyte('A');
        // led_on(1);
        delay_us(1000 * 50);
        // led_on(0);
        delay_us(1000 * 50);
        // sched();
    }
}

void fault_handler()
{
    // usart_sendline("fault...");
    while (1)
        ;
}

// void int_TIM2()
// {
//     usart_sendline("int_TIM2");
//     SET_BIT_32(TIM2->SR, 0, 0);
//     kernel_mode();
// }