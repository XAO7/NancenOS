#ifndef SYSCALLS_H
#define SYSCALLS_H

#include <NancenOSConfig.h>

#define SYSCALL_TABLE ((Syscall_Table *) SYSCALL_TABLE_START)

enum ENUM_SYSCALLS
{
    SysCall_UserMode = 0,
    SysCall_Sleep = 1,
};

typedef void (*syscall_t)(void *arg);

typedef struct Syscall_Table
{
    syscall_t syscalls[16];
} Syscall_Table;

#endif