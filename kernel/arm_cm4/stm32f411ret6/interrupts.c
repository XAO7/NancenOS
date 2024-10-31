#include <stdint.h>
#include <sys.h>

void Fault_Handler()
{
    __Fault_Handler();
}

void Int_SVC(uint32_t syscallNum, void *arg)
{
    __Int_SysCall(syscallNum, arg);
}

void Int_SYSTICK()
{
    __Int_SysTick();
}