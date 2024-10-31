#include <sys.h>
#include <asm.h>
#include <mem.h>
#include <timer.h>
#include <log.h>
#include <syscalls.h>

extern Task *taskList;
extern Task *currentTask;

void Sys_Init()
{
    taskList = NULL;
    Mem_Init();
    __Sys_InitTick();
    Log_Init();
}

void Sys_StartScheduler()
{
    __Sys_StartTick();

    while (1)
    {
        currentTask = __Sys_Scheduler();
        __Task_Run(currentTask);

        // Log_SendLine("sc");
    }
}

void Sys_Call(uint32_t syscallNum, void *arg)
{
    __Sys_Call(syscallNum, arg);
}

Task *__Sys_Scheduler()
{
    Task *toRun = __Task_GetMaxTicks();
    if (toRun->curTicks == 0)
    {
        __Task_ResetTicks();
        toRun = __Task_GetMaxTicks();
    }

    (toRun->curTicks)--;

    return toRun;
}

// Interrupt handlers implementation
void __Fault_Handler()
{
    Log_SendLine("Fault");
    while (1)
        ;
}

void __Int_SysCall(uint32_t syscallNum, void *arg)
{
    SYSCALL_TABLE->syscalls[syscallNum](arg);
}

void __Int_SysTick()
{
    __Sys_DisableTickInt();
    __Sys_KernelMode((uint32_t *)&(currentTask->taskRegs));
}