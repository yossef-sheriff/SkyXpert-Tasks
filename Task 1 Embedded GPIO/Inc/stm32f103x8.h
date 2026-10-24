/*
 *  stm32f103x8.h
 *
 *  Created on: Jan 11, 2026
 *  Author: Mohamed Ragab
 */

#ifndef INC_STM32F103X8_H_
#define INC_STM32F103X8_H_

#include "stdlib.h"
#include <stdint.h>


//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
// Base Addresses for Memories
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
#define Flash_Memory_Base 					0x08000000UL
#define System_Memory_Base 					0x1FFFF000UL
#define SRAM_Memory_Base 					0x20000000UL

#define Peripherals_Base 					0x40000000UL
#define Cortex_M3_internal_Peripherals 		0xE0000000UL


//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
// Base Addresses for APB Bus
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*

/*
#define TIM_2_Base 					(Peripherals_Base + 0x000UL)
#define TIM_3_Base 					(Peripherals_Base + 0x400UL)
#define TIM_4_Base 					(Peripherals_Base + 0x800UL)

#define RTC_Base 					(Peripherals_Base + 0x2800UL)
#define WWDG_Base 					(Peripherals_Base + 0x2C00UL)
#define IWDG_Base 					(Peripherals_Base + 0x3000UL)
*/

/*
#define SPI_2_Base 					(Peripherals_Base + 0x3800UL)
*/

/*
#define USART_2_Base 				(Peripherals_Base + 0x4400UL)
#define USART_3_Base 				(Peripherals_Base + 0x4800UL)
*/

// I2C
#define I2C_1_Base 					(Peripherals_Base + 0x00005400UL)
#define I2C_2_Base 					(Peripherals_Base + 0x00005800UL)

#define USB_registers_Base 			(Peripherals_Base + 0x00005C00UL)
#define USB_CAN_Base 			    (Peripherals_Base + 0x00006000UL)
#define bxCAN_Base 					(Peripherals_Base + 0x00006400UL)

#define BKP_Base 					(Peripherals_Base + 0x00006C00UL)
#define PWR_Base 					(Peripherals_Base + 0x00007000UL)

//___GPIO___
// PORT A
#define GPIO_A_BASE 				(Peripherals_Base + 0x00010800UL)
// PORT B
#define GPIO_B_BASE 				(Peripherals_Base + 0x00010C00UL)
// PORT C
#define GPIO_C_BASE 				(Peripherals_Base + 0x00011000UL)
// PORT D
#define GPIO_D_BASE 				(Peripherals_Base + 0x00011400UL)
// PORT E
#define GPIO_E_BASE 				(Peripherals_Base + 0x00011800UL)
//___INTERRUPT___
#define EXTI_BASE					(Peripherals_Base + 0x00010400UL)
//___Alternative IO___
#define AFIO_BASE					(Peripherals_Base + 0x00010000UL)

// ADC
#define ADC_1_Base 					(Peripherals_Base + 0x00012400UL)
#define ADC_2_Base 					(Peripherals_Base + 0x00012800UL)

// Timer
#define TIM_1_Base 					(Peripherals_Base + 0x00012C00UL)
#define TIM_2_Base 					(Peripherals_Base + 0x00000000UL)
#define TIM_3_Base 					(Peripherals_Base + 0x00000400UL)
#define TIM_4_Base 					(Peripherals_Base + 0x00000800UL)
#define RCC_Base 					(Peripherals_Base + 0x00021000UL)
#define RTC_Base 					(Peripherals_Base + 0x00002800UL)
#define WWDG_Base 					(Peripherals_Base + 0x00002C00UL)
#define IWDG_Base 					(Peripherals_Base + 0x00003000UL)


// SPI
#define SPI_1_Base 					(Peripherals_Base + 0x00013000UL)
#define SPI_2_Base 					(Peripherals_Base + 0x00003800UL)

// USART
#define USART_1_Base 				(Peripherals_Base + 0x00013800UL)
#define USART_2_Base 				(Peripherals_Base + 0x00004400UL)
#define USART_3_Base 				(Peripherals_Base + 0x00004800UL)

#define DMA_Base 					(Peripherals_Base + 0x00020000UL)

/*
#define RCC_Base 					(Peripherals_Base + 0x21000UL)
*/

#define Flash_interface_Base 		(Peripherals_Base + 0x00022000UL)

#define CRC_Base 					(Peripherals_Base + 0x00023000UL)



//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
// Peripheral Registers
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*

// GPIO Registers
typedef struct
{
	volatile uint32_t GPIO_CRL;
	volatile uint32_t GPIO_CRH;
	volatile uint32_t GPIO_IDR;
	volatile uint32_t GPIO_ODR;
	volatile uint32_t GPIO_BSRR;
	volatile uint32_t GPIO_BRR;
	volatile uint32_t GPIO_LCKR;
}GPIO_TypeDef;


// AFIO Registers
typedef struct
{
	volatile uint32_t AFIO_EVCR;
	volatile uint32_t AFIO_MAPR;
	volatile uint32_t AFIO_EXTICR1;
	volatile uint32_t AFIO_EXTICR2;
	volatile uint32_t AFIO_EXTICR3;
	volatile uint32_t AFIO_EXTICR4;
	uint32_t 			  reserved;
	volatile uint32_t AFIO_MAPR2;
}AFIO_TypeDef;

// RCC Registers
typedef struct
{
	volatile uint32_t RCC_CR;
	volatile uint32_t RCC_CFGR;
	volatile uint32_t RCC_CIR;
	volatile uint32_t RCC_APB2RSTR;
	volatile uint32_t RCC_APB1RSTR;
	volatile uint32_t RCC_AHBENR;
	volatile uint32_t RCC_APB2ENR;
	volatile uint32_t RCC_APB1ENR;
	volatile uint32_t RCC_BDCR;
	volatile uint32_t RCC_CSR;
}RCC_TypeDef;

// EXTI Registers
typedef struct
{
	volatile uint32_t EXTI_IMR;
	volatile uint32_t EXTI_EMR;
	volatile uint32_t EXTI_RTSR;
	volatile uint32_t EXTI_FTSR;
	volatile uint32_t EXTI_SWIER;
	volatile uint32_t EXTI_PR;
}EXTI_TypeDef;


//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
// Peripheral Instants
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
#define GPIO_A  		((GPIO_TypeDef*)GPIO_A_BASE)
#define GPIO_B			((GPIO_TypeDef*)GPIO_B_BASE)
#define GPIO_C			((GPIO_TypeDef*)GPIO_C_BASE)
#define GPIO_D			((GPIO_TypeDef*)GPIO_D_BASE)
#define GPIO_E			((GPIO_TypeDef*)GPIO_E_BASE)

#define RCC				((RCC_TypeDef*)RCC_Base)

#define EXTI 			((EXTI_TypeDef*)EXTI_BASE)

#define AFIO			((AFIO_TypeDef*)AFIO_BASE)


//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
// Clock Enable
//_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*_*
#define RCC_AFIO_CLK_EN()			(RCC->RCC_APB2ENR |= 1<<0)
#define RCC_GPIO_A_CLK_EN()		    (RCC->RCC_APB2ENR |= 1<<2)
#define RCC_GPIO_B_CLK_EN()			(RCC->RCC_APB2ENR |= 1<<3)
#define RCC_GPIO_C_CLK_EN()			(RCC->RCC_APB2ENR |= 1<<4)
#define RCC_GPIO_D_CLK_EN()			(RCC->RCC_APB2ENR |= 1<<5)
#define RCC_GPIO_E_CLK_EN()			(RCC->RCC_APB2ENR |= 1<<6)


#endif /* INC_STM32F103X8_H_ */
