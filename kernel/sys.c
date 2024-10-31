#include <sys.h>
#include <asm.h>
#include <mem.h>
#include <timer.h>
#include <log.h>
#include <syscalls.h>

extern Task *taskList;
extern Task *currentTask;
extern Task *taskIdle;

void Sys_Init()
{
    Mem_Init();

    taskList = NULL;
    taskIdle = Task_New(task_idle, 1, 0);
    taskList = NULL;

    __Sys_InitTick();
    Log_Init();
}

void Sys_Call(uint32_t syscallNum, void *arg)
{
    __Sys_Call(syscallNum, arg);
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