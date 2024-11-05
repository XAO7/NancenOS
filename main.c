#include <sys.h>
#include <log.h>

volatile uint32_t a, b;

void task0()
{
    while (1)
    {
        Log_Printf("a is %d", NULL, a, 0);
        Log_Printf("b is %d", NULL, b, 0);
        Log_SendLine("=============");
        Task_Sleep(400);
    }
}

void task1()
{
    a = 0;
    while (1)
    {
        a++;
    }
}

void task2()
{
    b = 0;
    while (1)
    {
        b++;
    }
}

void task3()
{
    while (1)
    {
        Log_SendLine("Meanwhile, I am sending a line and there's no conflict!");
        Task_Sleep(100);
    }
}

void main()
{
    Sys_Init();

    Task_New(task0, 1, 1024);
    Task_New(task1, 2, 1024);
    Task_New(task2, 3, 1024);
    Task_New(task3, 1, 1024);

    Sys_StartScheduler();

    while (1)
    {
        // Shouldn't be reaching here
        ;
    }
}