#ifndef LOG_H
#define LOG_H

#include <stdint.h>

void Log_Init();
void Log_SendLine(uint8_t *str);

#endif