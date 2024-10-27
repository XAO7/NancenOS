#include <log.h>
#include <tasks.h>
#include <asm.h>

void Fault_Handler()
{
    Log_SendLine("fault...");
    while (1)
        ;
}

void Int_SVC()
{
    __Int_SVC();
}

void Int_SYSTICK()
{
    __Int_SYSTICK();
}