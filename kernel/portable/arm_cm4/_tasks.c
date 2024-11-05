#include <_tasks.h>
#include <mem.h>

void __Task_Init(Task* task)
{
    // Allocate stack and set up return frame
    uint32_t *taskStackBottom = Mem_Alloc(task->stackSize + 8 * 4);
    uint32_t *taskStack = taskStackBottom + task->stackSize;
    taskStack[5] = ((uint32_t)task->taskFunc);
    taskStack[6] = ((uint32_t)task->taskFunc) - 1;
    taskStack[7] = (uint32_t)0x01000000;

    // Set up SP
    task->taskRegs.SP = (uint32_t)taskStack;
}