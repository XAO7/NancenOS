#ifndef STM32F411RET6_GPIO_H
#define STM32F411RET6_GPIO_H

#include <stdint.h>

typedef enum ENUM_GPIO_Port
{
    GPIO_A = 0,
    GPIO_B = 1,
    GPIO_C = 2,
    GPIO_D = 3,
    GPIO_E = 4,
    GPIO_H = 7,
} ENUM_GPIO_Port;

typedef enum ENUM_GPIO_Mode
{
    GPIO_Mode_Input = 0,
    GPIO_Mode_Output = 1,
    GPIO_Mode_AF = 2,
    GPIO_Mode_Analog = 3,
} ENUM_GPIO_Mode;

typedef enum ENUM_GPIO_OutputType
{
    GPIO_OutputType_PushPull = 0,
    GPIO_OutputType_OpenDrain = 1,
} ENUM_GPIO_OutputType;

typedef enum ENUM_GPIO_OutputSpeed
{
    GPIO_OutputSpeed_Low = 0,
    GPIO_OutputSpeed_Medium = 1,
    GPIO_OutputSpeed_Fast = 2,
    GPIO_OutputSpeed_Hign = 3,
} ENUM_GPIO_OutputSpeed;

typedef struct GPIO_Setting
{
    uint8_t port;
    uint8_t num;
    uint8_t mode;
    uint8_t outputType;
    uint8_t outputSpeed;
} GPIO_Setting;

typedef struct GPIO_Which
{
    uint8_t port;
    uint8_t num;
} GPIO_Which;

void GPIO_Init(GPIO_Setting *setting);
void GPIO_Set(GPIO_Setting *setting);

void GPIO_Output(GPIO_Which *which, uint8_t out);

#endif