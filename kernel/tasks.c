#include <tasks.h>
#include <asm.h>
#include <mem.h>
#include <timer.h>
#include <log.h>
#include <sys.h>
#include <syscalls.h>

Task *taskList;
Task *currentTask;
Task *idleTask;

Task *Task_New(task_func_t taskFunc, uint8_t priority, size_t stackSize)
{
    Task *newTask = Mem_Alloc(sizeof(Task));
    newTask->taskFunc = taskFunc;
    newTask->stackSize = stackSize;
    newTask->priority = priority;
    newTask->curTicks = priority;
    newTask->sleepTicks = 0;
    newTask->next = NULL;

    __Task_Init(newTask);

    if (taskList == NULL)
    {
        taskList = newTask;
        return newTask;
    }

    Task *current = taskList;

    while (current->next != NULL)
        current = current->next;

    current->next = newTask;

    return newTask;
}

void Task_Sleep(uint16_t ticks)
{
    Sys_Call(SysCall_Sleep, (void *)(uint32_t)ticks);
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

Task *__Sys_Scheduler()
{
    Task *toRun = __Task_GetMaxTicks();
    if (toRun == NULL)
    {
        __Task_DecSleepTicks();

        return idleTask;
    }

    if (toRun->curTicks == 0)
    {
        __Task_ResetTicks();
        toRun = __Task_GetMaxTicks();
    }

    (toRun->curTicks)--;

    __Task_DecSleepTicks();

    return toRun;
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
        if (current->sleepTicks == 0)
        {
            if (result == taskList && result->sleepTicks > 0)
            {
                if (current->curTicks >= 0)
                    result = current;
            }
            else if (current->curTicks > result->curTicks)
                result = current;
        }
        current = current->next;
    }

    if (result->sleepTicks == 0)
        return result;
    else
        // All sleeping
        return NULL;
}

void __Task_DecSleepTicks()
{
    Task *current = taskList;

    while (current != NULL)
    {
        if (current->sleepTicks > 0)
            current->sleepTicks--;

        current = current->next;
    }
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

void __Task_Idle()
{
    while (1)
        ;
}

void __SysCall_Sleep(uint16_t ticks)
{
    __Sys_DisableTickInt();

    currentTask->sleepTicks = ticks;

    __Sys_KernelMode((uint32_t *)&(currentTask->taskRegs));
}