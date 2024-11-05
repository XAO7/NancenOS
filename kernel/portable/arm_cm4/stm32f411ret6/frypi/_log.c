#include <log.h>
#include <stm32f411ret6_usart.h>

void __Log_Init()
{
    USART_Init();
}

void __Log_SendByte(uint8_t b)
{
    USART_SendByte(b);
}