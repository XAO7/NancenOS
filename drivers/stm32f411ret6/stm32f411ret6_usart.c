#include <stm32f411ret6_usart.h>
#include <stm32f411ret6.h>
#include <tools.h>

void usart_init()
{
    // Enable the clock for USART1
    SET_BIT(RCC->APB2ENR, 4, 1);

    // Enable the clock for GPIOA
    SET_BIT(RCC->AHB1ENR, 0, 1);

    // Set the baud rate for USART1
    SET_HW_32(USART1->BRR, 0, ((0x145 << 4) | 0x8));

    // Enable the USART1 by setting the bit 13 in CR1 register (UE: USART enable)
    SET_BIT(USART1->CR1, 13, 1);

    // Enable the transmitter by setting the bit 3 in CR1 register (TE: Transmitter enable)
    SET_BIT(USART1->CR1, 3, 1);

    // Configure PA9 to alternate function mode
    SET_BIT_32(GPIOA->MODER, 19, 1);

    // Configure PA9 to alternate function 7
    SET_BYTE_32(GPIOA->AFRH, 0, 0x70);
}

void usart_sendbyte(uint8_t b)
{
    while (!((USART1->SR) & 0x80))
        ;
    SET_BYTE(USART1->DR, 0, b);
}

void usart_sendline(uint8_t *str)
{
    while (*str)
    {
        usart_sendbyte(*str);
        str++;
    }
    usart_sendbyte('\n');
}

void usart_printf(const uint8_t *format, const uint8_t *s_arg, int32_t d_arg, uint32_t x_arg)
{
    const uint8_t *p = format;

    while (*p)
    {
        if (*p == '%')
        {
            p++;
            if (*p == 's')
            {
                while (*s_arg)
                {
                    usart_sendbyte(*s_arg++);
                }
            }
            else if (*p == 'd')
            {
                int32_t num = d_arg;
                if (num < 0)
                {
                    usart_sendbyte('-');
                    num = -num;
                }

                uint8_t buffer[10];
                int32_t i = 0;
                do
                {
                    buffer[i++] = (num % 10) + '0';
                    num /= 10;
                } while (num);

                while (i--)
                {
                    usart_sendbyte(buffer[i]);
                }
            }
            else if (*p == 'x')
            {
                uint32_t num = x_arg;
                uint8_t buffer[8];
                int32_t i = 0;

                do
                {
                    int32_t digit = num % 16;
                    if (digit < 10)
                    {
                        buffer[i++] = digit + '0';
                    }
                    else
                    {
                        buffer[i++] = digit - 10 + 'a';
                    }
                    num /= 16;
                } while (num);

                while (i--)
                {
                    usart_sendbyte(buffer[i]);
                }
            }
        }
        else
        {
            usart_sendbyte(*p);
        }
        p++;
    }
}