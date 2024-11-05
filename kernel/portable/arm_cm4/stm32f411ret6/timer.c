#include <timer.h>
#include <arm_cm4.h>
#include <tools.h>

void __Sys_InitTick()
{
    // 100M / 8 / 1000 (1ms)
    SET_HW_32(SYST->RVR, 0, 12500);
    // SET_HW_32(SYST->RVR, 0, 0);
    SET_HW_32(SYST->CVR, 0, 0);
}

void __Sys_StartTick()
{
    // Enable SYSTICK
    SET_BIT_32(SYST->CSR, 0, 1);
}

void __Sys_EnableTickInt()
{
    // Enable TICKINT
    SET_BIT_32(SYST->CSR, 1, 1);
}

void __Sys_DisableTickInt()
{
    // Disable TICKINT
    SET_BIT_32(SYST->CSR, 1, 0);
}
