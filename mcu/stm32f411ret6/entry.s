.thumb
.syntax unified

.global entry
.extern main
.extern fault_handler
.extern int_TIM2
.extern __int_SVC

@ msp
    .int 0x20020000
@ ip
    .int entry+1
.rept 80
    .int fault_handler+1
.endr
@ . = 11 * 4
@ .int __int_SVC + 1
@ . = 0x000000B0
@ .int int_TIM2 + 1

entry:
    bl main
