#ifndef STM32F411RET6_H
#define STM32F411RET6_H

#include <stdint.h>

#define PERIPH_BASE ((uint32_t)0x40000000)

#define APB1PERIPH_BASE PERIPH_BASE
#define APB2PERIPH_BASE (PERIPH_BASE + 0x10000)
#define AHB1PERIPH_BASE (PERIPH_BASE + 0x20000)

#define TIM2_BASE (APB1PERIPH_BASE)
#define TIM3_BASE (APB1PERIPH_BASE + 0x400)
#define TIM4_BASE (APB1PERIPH_BASE + 0x800)
#define TIM5_BASE (APB1PERIPH_BASE + 0xC00)

#define USART1_BASE (APB2PERIPH_BASE + 0X1000)

#define GPIOA_BASE (AHB1PERIPH_BASE + 0x0)
#define GPIOB_BASE (AHB1PERIPH_BASE + 0x400)
#define GPIOC_BASE (AHB1PERIPH_BASE + 0x800)
#define GPIOD_BASE (AHB1PERIPH_BASE + 0xC00)
#define GPIOE_BASE (AHB1PERIPH_BASE + 0x1000)
#define GPIOH_BASE (AHB1PERIPH_BASE + 0x1C00)
#define RCC_BASE (AHB1PERIPH_BASE + 0x3800)
#define FLASH_BASE (AHB1PERIPH_BASE + 0x3C00)

#define TIM2 ((TIM_TypeDef *)TIM2_BASE)
#define TIM3 ((TIM_TypeDef *)TIM3_BASE)
#define TIM4 ((TIM_TypeDef *)TIM4_BASE)
#define TIM5 ((TIM_TypeDef *)TIM5_BASE)

#define USART1 ((USART_TypeDef *)USART1_BASE)

#define GPIOA ((GPIO_TypeDef *)GPIOA_BASE)
#define GPIOB ((GPIO_TypeDef *)GPIOB_BASE)
#define GPIOC ((GPIO_TypeDef *)GPIOC_BASE)
#define GPIOD ((GPIO_TypeDef *)GPIOD_BASE)
#define GPIOE ((GPIO_TypeDef *)GPIOE_BASE)
#define GPIOH ((GPIO_TypeDef *)GPIOH_BASE)
#define RCC ((RCC_TypeDef *)RCC_BASE)
#define FLASH ((FLASH_TypeDef *)FLASH_BASE)

typedef struct TIM_TypeDef
{
    volatile uint32_t CR1;
    volatile uint32_t CR2;
    volatile uint32_t SMCR;
    volatile uint32_t DIER;
    volatile uint32_t SR;
    volatile uint32_t EGR;
    volatile uint64_t CCMR1;
    volatile uint64_t CCMR2;
    volatile uint32_t CCER;
    volatile uint32_t CNT;
    volatile uint32_t PSC;
    volatile uint32_t ARR;
    volatile uint32_t _RESERVED1;
    volatile uint32_t CCR1;
    volatile uint32_t CCR2;
    volatile uint32_t CCR3;
    volatile uint32_t CCR4;
    volatile uint32_t _RESERVED2;
    volatile uint32_t DCR;
    volatile uint32_t DMAR;
    volatile uint32_t OR;
} TIM_TypeDef;

typedef struct USART_TypeDef
{
    volatile uint32_t SR;   /*!< USART Status register,                   Address offset: 0x00 */
    volatile uint32_t DR;   /*!< USART Data register,                     Address offset: 0x04 */
    volatile uint32_t BRR;  /*!< USART Baud rate register,                Address offset: 0x08 */
    volatile uint32_t CR1;  /*!< USART Control register 1,                Address offset: 0x0C */
    volatile uint32_t CR2;  /*!< USART Control register 2,                Address offset: 0x10 */
    volatile uint32_t CR3;  /*!< USART Control register 3,                Address offset: 0x14 */
    volatile uint32_t GTPR; /*!< USART Guard time and prescaler register, Address offset: 0x18 */
} USART_TypeDef;

typedef struct GPIO_TypeDef
{
    volatile uint32_t MODER;   /*!< GPIO port mode register, Address offset: 0x00 */
    volatile uint32_t OTYPER;  /*!< GPIO port output type register, Address offset: 0x04 */
    volatile uint32_t OSPEEDR; /*!< GPIO port output speed register, Address offset: 0x08 */
    volatile uint32_t PUPDR;   /*!< GPIO port pull-up/pull-down register, Address offset: 0x0C */
    volatile uint32_t IDR;     /*!< GPIO port input data register, Address offset: 0x10 */
    volatile uint32_t ODR;     /*!< GPIO port output data register, Address offset: 0x14 */
    volatile uint32_t BSRR;    /*!< GPIO port bit set/reset register, Address offset: 0x18 */
    volatile uint32_t LCKR;    /*!< GPIO port configuration lock register, Address offset: 0x1C */
    volatile uint32_t AFRL;    /*!< GPIO alternate function low register, Address offset: 0x20 */
    volatile uint32_t AFRH;    /*!< GPIO alternate function high register, Address offset: 0x24 */
} GPIO_TypeDef;

typedef struct RCC_TypeDef
{
    volatile uint32_t CR;       /*!< Clock control register, Address offset: 0x00 */
    volatile uint32_t PLLCFGR;  /*!< PLL configuration register, Address offset: 0x04 */
    volatile uint32_t CFGR;     /*!< Clock configuration register, Address offset: 0x08 */
    volatile uint32_t CIR;      /*!< Clock interrupt register, Address offset: 0x0C */
    volatile uint32_t AHB1RSTR; /*!< AHB1 peripheral reset register, Address offset: 0x10 */
    volatile uint32_t AHB2RSTR; /*!< AHB2 peripheral reset register, Address offset: 0x14 */
    volatile uint32_t _RESERVED1[2];
    volatile uint32_t APB1RSTR; /*!< APB1 peripheral reset register, Address offset: 0x20 */
    volatile uint32_t APB2RSTR; /*!< APB2 peripheral reset register, Address offset: 0x24 */
    volatile uint32_t _RESERVED2[2];
    volatile uint32_t AHB1ENR; /*!< AHB1 peripheral clock enable register, Address offset: 0x30 */
    volatile uint32_t AHB2ENR; /*!< AHB2 peripheral clock enable register, Address offset: 0x34 */
    volatile uint32_t _RESERVED3[2];
    volatile uint32_t APB1ENR; /*!< APB1 peripheral clock enable register, Address offset: 0x40 */
    volatile uint32_t APB2ENR; /*!< APB2 peripheral clock enable register, Address offset: 0x44 */
    volatile uint32_t _RESERVED4[2];
    volatile uint32_t AHB1LPENR;
    volatile uint32_t AHB2LPENR;
    volatile uint32_t _RESERVED5[2];
    volatile uint32_t APB1LPENR;
    volatile uint32_t APB2LPENR;
    volatile uint32_t _RESERVED6[2];
    volatile uint32_t BDCR; /*!< Backup domain control register, Address offset: 0x70 */
    volatile uint32_t CSR;  /*!< Clock control & status register, Address offset: 0x74 */
    volatile uint32_t _RESERVED7[2];
    volatile uint32_t SSCGR;
    volatile uint32_t PLLI2SCFGR;
    volatile uint32_t _RESERVED8;
    volatile uint32_t DCKCFGR;
} RCC_TypeDef;

typedef struct FLASH_TypeDef
{
    volatile uint32_t ACR;     /*!< FLASH Access Control Register, Address offset: 0x00 */
    volatile uint32_t KEYR;    /*!< FLASH Key Register, Address offset: 0x04 */
    volatile uint32_t OPTKEYR; /*!< FLASH Option Key Register, Address offset: 0x08 */
    volatile uint32_t SR;      /*!< FLASH Status Register, Address offset: 0x0C */
    volatile uint32_t CR;      /*!< FLASH Control Register, Address offset: 0x10 */
    volatile uint32_t OPTCR;   /*!< FLASH Option Control Register, Address offset: 0x14 */
} FLASH_TypeDef;

#endif