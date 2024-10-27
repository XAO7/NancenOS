#ifndef MEM_H
#define MEM_H

#include <stdint.h>

extern const uint32_t __bss_start;
extern const uint32_t __bss_end;

typedef struct MemoryBlock {
    size_t size;                  // Size of the memory block (excluding header)
    struct MemoryBlock* next;     // Pointer to the next free block
} Mem_Block;

void Mem_Init();
void* Mem_Alloc(size_t size);
void Mem_Free(void *ptr);


#endif