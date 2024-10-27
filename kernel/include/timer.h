#ifndef TIMER_H
#define TIMER_H

void __Sys_InitTick();
void __Sys_StartTick();
void __Sys_EnableTickInt();
void __Sys_DisableTickInt();

#endif