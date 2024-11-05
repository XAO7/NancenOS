#ifndef CONFIG_H
#define CONFIG_H

#include <stm32f411ret6.h>

#define MEM_START SRAM_BASE
#define MEM_END (SRAM_BASE + SRAM_SIZE)

#define HEAP_SIZE (120 * 1024)
#define SYSCALL_TABLE_START (0x00000198)

#endif