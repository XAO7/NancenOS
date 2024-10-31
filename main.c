#include <stm32f411ret6_init.h>
#include <stm32f411ret6_usart.h>

#include <tasks.h>
#include <sys.h>

volatile uint32_t t0, t1, t2;

void task0()
{
    while (1)
    {
        t0++;
    }
}

void task1()
{
    while (1)
    {
        t1++;
    }
}

void task2()
{
    while (1)
    {
        t2++;
    }
}

void print()
{
    USART_Printf("%d ", NULL, t0, 0);
    USART_Printf("%d ", NULL, t1, 0);
    USART_Printf("%d ", NULL, t2, 0);
    USART_SendLine("");
}

void main()
{
    MCU_Init();
    USART_Init();

    Sys_Init();

    Task_New(task0, 1, 1024);
    Task_New(task1, 2, 1024);
    Task_New(task2, 3, 1024);
    Task_New(print, 1, 1024);

    t0 = t1 = t2 = 0;

    Sys_StartScheduler();

    while (1)
    {
        // Shouldn't be reaching here
        ;
    }
}