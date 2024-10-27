#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>

typedef void (*task_func_t)();

typedef struct Task_Regs
{
    uint32_t R4;
    uint32_t R5;
    uint32_t R6;
    uint32_t R7;
    uint32_t R8;
    uint32_t R9;
    uint32_t R10;
    uint32_t R11;
    uint32_t SP;
} Task_Regs;

typedef struct Task
{
    uint8_t taskID;
    task_func_t taskFunc;
    struct Task_Regs taskRegs;
    struct Task *next;
} Task;

void Task_New(task_func_t taskFunc, size_t stackSize);
void Sys_Init();
void Sys_StartScheduler();

void _Task_Run(Task *task);

void __Int_SYSTICK();

#endif