#ifndef SYS_H
#define SYS_H

#include <_sys.h>
#include <stdint.h>
#include <tasks.h>

void Sys_Init();
void Sys_Call(uint32_t syscallNum, void *arg);

void __Fault_Handler();
void __Int_SysCall();
void __Int_SysTick();

#endif