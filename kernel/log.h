#ifndef LOG_H
#define LOG_H

#include <stdint.h>

#include <_log.h>

void task_logger();

void Log_Init();
void Log_SendByte(uint8_t b);
void Log_SendLine(uint8_t *str);
void Log_Printf(uint8_t *format, uint8_t *s_arg, int32_t d_arg, uint32_t x_arg);

#endif