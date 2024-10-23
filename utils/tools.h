#ifndef TOOLS_H
#define TOOLS_H

#include <stdint.h>

#define SET_HW_32(dst, index, hw)         \
    do                                    \
    {                                     \
        uint32_t tmp32 = dst;             \
        ((uint16_t *)&tmp32)[index] = hw; \
        dst = tmp32;                      \
    } while (0)
#define SET_BYTE_32(dst, index, byte)      \
    do                                     \
    {                                      \
        uint32_t tmp32 = dst;              \
        ((uint8_t *)&tmp32)[index] = byte; \
        dst = tmp32;                       \
    } while (0)
#define SET_BYTE(dst, index, byte)       \
    do                                   \
    {                                    \
        ((uint8_t *)&dst)[index] = byte; \
    } while (0)
#define SET_BIT_32(dst, index, bit)                                      \
    do                                                                   \
    {                                                                    \
        uint32_t tmp32 = bit ? dst | (1 << index) : dst & ~(1 << index); \
        dst = tmp32;                                                     \
    } while (0)
#define SET_BIT(dst, index, bit)                              \
    do                                                        \
    {                                                         \
        dst = bit ? dst | (1 << index) : dst & ~(1 << index); \
    } while (0)
#define SET_BIT_BAND(dst, index, bit)                                                        \
    do                                                                                       \
    {                                                                                        \
        *((uint8_t *)(0x42000000 + ((uint32_t) & dst - 0x40000000) * 32 + index * 4)) = bit; \
    } while (0)

#define DELAY(c)                \
    for (int i = 0; i < c; i++) \
    {                           \
        asm("nop");             \
    }

#endif