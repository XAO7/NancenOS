#ifndef STM32F411RET6_USART_H
#define STM32F411RET6_USART_H

#include <stdint.h>

void usart_init();
void usart_sendbyte(uint8_t b);
void usart_sendline(uint8_t *str);
void usart_printf(const uint8_t *format, const uint8_t *s_arg, int32_t d_arg, uint32_t x_arg);

#endif