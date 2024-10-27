#include <log.h>
#include <stm32f411ret6_usart.h>

void Log_Init()
{
    USART_Init();
}

void Log_SendLine(uint8_t *str)
{
    USART_SendLine(str);
}