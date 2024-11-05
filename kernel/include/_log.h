#ifndef _LOG_H
#define _LOG_H

#include <stdint.h>

void __Log_Init();
void __Log_SendByte(uint8_t b);

#endif