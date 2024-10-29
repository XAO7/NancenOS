#include <tasks.h>
#include <asm.h>
#include <mem.h>
#include <timer.h>
#include <log.h>

static Task *taskList;
static Task *currentTask;

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

void __Task_Run(Task *task)
{
    __Sys_EnableTickInt();
    __Sys_UserMode((uint32_t *)&(task->taskRegs));
}

Task *__Sys_Scheduler()
{
    Task *toRun = __Task_GetMaxTicks();
    if (toRun->curTicks == 0)
        __Task_ResetTicks();

    (toRun->curTicks)--;

    return toRun;
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

void __Int_SYSTICK()
{
    __Sys_DisableTickInt();
    __Sys_KernelMode((uint32_t *)&(currentTask->taskRegs));
}
