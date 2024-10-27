#include <stm32f411ret6_init.h>
#include <stm32f411ret6_usart.h>

#include <tasks.h>

void task0()
{
    while (1)
    {
        USART_SendLine("task0");
    }
}

void task1()
{
    while (1)
    {
        USART_SendLine("task1");
    }
}

void main()
{
    MCU_Init();
    USART_Init();

    Sys_Init();

    Task_New(task0, 1024);
    Task_New(task1, 1024);

    Sys_StartScheduler();

    while (1)
    {
        // Shouldn't be reaching here
        ;
    }
}