#ifndef ASM_H
#define ASM_H

#include <stdint.h>

void __Sys_UserMode(uint32_t *regs);
void __Sys_KernelMode(uint32_t *regs);

void __Int_SVC();

#endif