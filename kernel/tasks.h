#ifndef TASKS_H
#define TASKS_H

#include <stdint.h>
#include <_tasks.h>

Task *Task_New(task_func_t taskFunc, uint8_t priority, size_t stackSize);
Task *Task_GetCurrent();
Task *Task_GetByFunction(task_func_t taskFunc);
void Task_Sleep(uint16_t ticks);

void Sys_StartScheduler();

Task *__Sys_Scheduler();

void __Task_Run(Task *task);
Task *__Task_GetMaxTicks();
void __Task_DecSleepTicks();
void __Task_ResetTicks();

void task_idle();

#endif