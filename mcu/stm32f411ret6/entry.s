.thumb
.syntax unified

.global entry

.extern main, Fault_Handler, Int_SVC, Int_SYSTICK

@ msp 128KB
    .int 0x20020000
@ ip
    .int entry + 1

.rept 9
    .int Fault_Handler + 1
.endr

    .int Int_SVC + 1

.rept 3
    .int Fault_Handler + 1
.endr

    .int Int_SYSTICK + 1

entry:
    BL main
