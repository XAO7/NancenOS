#ifndef ASM_H
#define ASM_H

#include <stdint.h>

void __Sys_Call(uint32_t syscallNum, void *arg);
void __Sys_KernelMode(uint32_t *regs);

#endif