.thumb
.syntax unified
.global __Sys_Call, __Sys_KernelMode, __SysCall_UserMode

__Sys_Call:
    SVC 0
    BX LR

__SysCall_UserMode:
    @ Save kernel regs
    LDR R1, =kernelSave
    STMIA R1!, {R4-R11}

    @ Set PSP to task stack bottom
    LDR R1, [R0, 8 * 4]
    MSR PSP, R1

    @ Restore task regs
    LDMIA R0!, {R4-R11}

    @ Return to thread mode, using PSP
    MOV LR, 0xFFFFFFFD
    BX LR

__Sys_KernelMode:
    @ Save task regs
    STMIA R0!, {R4-R11}

    @ Save PSP
    MRS R1, PSP
    STR R1, [R0]

    @ Restore kernel regs
    LDR R1, =kernelSave
    LDMIA R1!, {R4-R11}

    @ Return to thread mode, using MSP
    MOV LR, 0xFFFFFFF9
    BX LR

.section .bss

kernelSave:
.rept 8
    .int 0x00000000
.endr