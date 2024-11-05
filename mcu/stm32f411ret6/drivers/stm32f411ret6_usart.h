#ifndef STM32F411RET6_USART_H
#define STM32F411RET6_USART_H

#include <stdint.h>

void USART_Init();
void USART_SendByte(uint8_t b);
void USART_SendLine(uint8_t *str);
void USART_Printf(const uint8_t *format, const uint8_t *s_arg, int32_t d_arg, uint32_t x_arg);

#endif