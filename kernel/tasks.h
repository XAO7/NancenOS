#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>
#include <_tasks.h>

void Task_New(task_func_t taskFunc, uint8_t priority, size_t stackSize);
void Sys_Init();
void Sys_StartScheduler();

Task *__Sys_Scheduler();

void __Task_Run(Task *task);
Task *__Task_GetMaxTicks();
void __Task_ResetTicks();

void __Int_SYSTICK();

#endif