#include <tasks.h>
#include <asm.h>
#include <mem.h>
#include <timer.h>
#include <log.h>

static Task *taskList;
static Task *currentTask;

void Task_New(task_func_t taskFunc, size_t stackSize)
{
    Task *newTask = Mem_Alloc(sizeof(Task));

    // Allocate stack and set up return frame
    uint32_t *taskStackBottom = Mem_Alloc(stackSize + 8 * 4);
    uint32_t *taskStack = taskStackBottom + stackSize;
    taskStack[5] = ((uint32_t)taskFunc);
    taskStack[6] = ((uint32_t)taskFunc) - 1;
    taskStack[7] = (uint32_t)0x01000000;

    newTask->taskRegs.SP = (uint32_t)taskStack;
    newTask->next = NULL;

    if (taskList == NULL)
    {
        taskList = newTask;
        return;
    }

    Task *currentTask = taskList;

    while (currentTask->next != NULL)
        currentTask = currentTask->next;

    currentTask->next = newTask;
}

void Sys_Init()
{
    taskList = NULL;
    Mem_Init();
    __Sys_InitTick();
}

void Sys_StartScheduler()
{
    __Sys_StartTick();
    currentTask = taskList;

    while (1)
    {
        _Task_Run(currentTask);
        if (currentTask->next == NULL)
            currentTask = taskList;
        else
            currentTask = currentTask->next;
    }
}

void _Task_Run(Task *task)
{
    __Sys_EnableTickInt();
    __Sys_UserMode((uint32_t *)&(task->taskRegs));
}

void __Int_SYSTICK()
{
    __Sys_DisableTickInt();
    __Sys_KernelMode((uint32_t *)&(currentTask->taskRegs));
}
