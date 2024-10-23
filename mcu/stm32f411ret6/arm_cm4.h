#ifndef ARM_CM4_H
#define ARM_CM4_H

#include <stdint.h>

#define SCS_BASE (0xE000E000) /*!< System Control Space Base Address */
#define SCB_BASE (SCS_BASE + 0x0D00)     /*!< System Control Block Base Address */

#define SCB ((SCB_TypeDef *)SCB_BASE)

typedef struct SCB_TypeDef
{
  volatile uint32_t CPUID;   /*!< Offset: 0x00  CPU ID Base Register                                  */
  volatile uint32_t ICSR;    /*!< Offset: 0x04  Interrupt Control State Register                      */
  volatile uint32_t VTOR;    /*!< Offset: 0x08  Vector Table Offset Register                          */
  volatile uint32_t AIRCR;   /*!< Offset: 0x0C  Application Interrupt / Reset Control Register        */
  volatile uint32_t SCR;     /*!< Offset: 0x10  System Control Register                               */
  volatile uint32_t CCR;     /*!< Offset: 0x14  Configuration Control Register                        */
  volatile uint32_t SHP[3];  /*!< Offset: 0x18  System Handlers Priority Registers (4-7, 8-11, 12-15) */
  volatile uint32_t SHCSR;   /*!< Offset: 0x24  System Handler Control and State Register             */
  volatile uint32_t CFSR;    /*!< Offset: 0x28  Configurable Fault Status Register                    */
  volatile uint32_t HFSR;    /*!< Offset: 0x2C  Hard Fault Status Register                            */
  volatile uint32_t DFSR;    /*!< Offset: 0x30  Debug Fault Status Register                           */
  volatile uint32_t MMFAR;   /*!< Offset: 0x34  Mem Manage Address Register                           */
  volatile uint32_t BFAR;    /*!< Offset: 0x38  Bus Fault Address Register                            */
  volatile uint32_t AFSR;    /*!< Offset: 0x3C  Auxiliary Fault Status Register                       */
  volatile uint32_t PFR[2];  /*!< Offset: 0x40  Processor Feature Register                            */
  volatile uint32_t DFR;     /*!< Offset: 0x48  Debug Feature Register                                */
  volatile uint32_t AFR;     /*!< Offset: 0x4C  Auxiliary Feature Register                            */
  volatile uint32_t MMFR[4]; /*!< Offset: 0x50  Memory Model Feature Register                         */
  volatile uint32_t ISAR[5]; /*!< Offset: 0x60  ISA Feature Register                                  */
} SCB_TypeDef;

#endif