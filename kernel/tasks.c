#include <tasks.h>
#include <asm.h>
#include <mem.h>
#include <timer.h>
#include <log.h>
#include <sys.h>
#include <syscalls.h>

Task *taskList;
Task *currentTask;

void Task_New(task_func_t taskFunc, uint8_t priority, size_t stackSize)
{
    Task *newTask = Mem_Alloc(sizeof(Task));
    newTask->taskFunc = taskFunc;
    newTask->stackSize = stackSize;
    newTask->priority = priority;
    newTask->curTicks = priority;
    newTask->next = NULL;

    __Task_Init(newTask);

    if (taskList == NULL)
    {
        taskList = newTask;
        return;
    }

    Task *current = taskList;

    while (current->next != NULL)
        current = current->next;

    current->next = newTask;
}

void Task_Sleep(uint16_t ticks)
{
    Sys_Call(SysCall_Sleep, (void *)(uint32_t)ticks);
}

void __Task_Run(Task *task)
{
    __Sys_EnableTickInt();
    Sys_Call(SysCall_UserMode, (void *)&(task->taskRegs));
}

Task *__Task_GetMaxTicks()
{
    Task *current = taskList;
    Task *result = taskList;

    while (current != NULL)
    {
        if (current->curTicks > result->curTicks)
            result = current;

        current = current->next;
    }

    return result;
}

void __Task_ResetTicks()
{
    Task *current = taskList;

    while (current != NULL)
    {
        current->curTicks = current->priority;

        current = current->next;
    }
}

void __SysCall_Sleep()
{
    
}