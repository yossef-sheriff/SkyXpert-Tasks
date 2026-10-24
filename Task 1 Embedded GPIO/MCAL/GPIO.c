/*
 * stm32f103c8_gpio_driver.c
 *
 *  Created on: Jan 11, 2026
 *      Author: Mohamed Ragab
 */

#include "GPIO.h"


uint8_t Get_CRLH_Position(uint16_t PinNumber)
{
	switch(PinNumber)
	{
	// CRL
	case GPIO_PIN_0:
		return 0;
		break;

	case GPIO_PIN_1:
		return 4;
		break;

	case GPIO_PIN_2:
		return 8;
		break;

	case GPIO_PIN_3:
		return 12;
		break;

	case GPIO_PIN_4:
		return 16;
		break;

	case GPIO_PIN_5:
		return 20;
		break;

	case GPIO_PIN_6:
		return 24;
		break;

	case GPIO_PIN_7:
		return 28;
		break;

		// CRH
	case GPIO_PIN_8:
		return 0;
		break;

	case GPIO_PIN_9:
		return 4;
		break;

	case GPIO_PIN_10:
		return 8;
		break;

	case GPIO_PIN_11:
		return 12;
		break;

	case GPIO_PIN_12:
		return 16;
		break;

	case GPIO_PIN_13:
		return 20;
		break;

	case GPIO_PIN_14:
		return 24;
		break;

	case GPIO_PIN_15:
		return 28;
		break;
	}
	return 0;
}



/**================================================================
 * @Fn 			- MCAL_GPIO_Init
 * @brief 		- Initializes the GPIOx PINy according to the specified parameters in the PinConfig.
 * @param [in]   - GPIOx: where x can be (A..E depending on used device) to select the GPIO peripheral.
 * @param [in]   - PinConfig: pointer to a GPIO_PinConfig_t structure that contains the configuration
 * 				  information for the specified GPIO PIN.
 * @retval 		- none
 * Note 			- STM32F103C8T6 MCU has GPIO A,B,C,D,E Modules
 * 				  But LQFP48 Package has only A, B, Part of C/D exported as external PINs from the MCU.
================================================================**/
void MCAL_GPIO_Init(GPIO_TypeDef *GPIOx, GPIO_PinConfig_t* PinConfig)
{
	// Port configuration register low  (GPIOx_CRL)
	// Port configuration register high (GPIOx_CRH)
	volatile uint32_t* configregister = NULL;
	uint8_t PIN_Speed_Config = 0;

	configregister = (PinConfig->GPIO_PinNumber < GPIO_PIN_8) ? &GPIOx->GPIO_CRL : &GPIOx->GPIO_CRH;

	// clear CNF[1:0] MODE[1:0]
	(*configregister) &= ~(0xf << Get_CRLH_Position(PinConfig->GPIO_PinNumber));

	// if PIN is output
	if( (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_AF_PP) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_OD) || (PinConfig->GPIO_MODE == GPIO_MODE_OUTPUT_PP))
	{
		// Set CNF[1:0] MODE[1:0]
		PIN_Speed_Config = ( (((PinConfig->GPIO_MODE - 4) << 2) | (PinConfig->GPIO_Output_Speed)) & 0x0f );
	}

	// if PIN is input
	else 	// MODE = 00: Input Mode (reset state)
	{
		if( (PinConfig->GPIO_MODE == GPIO_MODE_INPUT_FLO) || (PinConfig->GPIO_MODE == GPIO_MODE_Analog) ){
			// Set CNF[1:0] MODE[1:0]: 00
			PIN_Speed_Config = ((((PinConfig->GPIO_MODE) << 2) | 0x0) & 0x0f);
		}
		else if(PinConfig->GPIO_MODE == GPIO_MODE_AF_INPUT) // Consider it as input floating
		{
			// Set CNF[1:0] MODE[1:0]: 00
			PIN_Speed_Config = ( (((GPIO_MODE_INPUT_FLO) << 2) | 0x0) & 0x0f);
		}
		else // PU/PD Input
		{
			PIN_Speed_Config = ( (((GPIO_MODE_INPUT_PU) << 2) | 0x0) & 0x0f);

			if(PinConfig->GPIO_MODE == GPIO_MODE_INPUT_PU)
			{
				// PxODR = 1 Input pull-up: Table 20. Port bit configuration table
				GPIOx->GPIO_ODR |= PinConfig->GPIO_PinNumber;
			}
			else
			{
				GPIOx->GPIO_ODR &= ~PinConfig->GPIO_PinNumber;
			}
		}
	}
	(*configregister) |= ( PIN_Speed_Config << Get_CRLH_Position(PinConfig->GPIO_PinNumber) );
}

/**================================================================
 * @Fn 			- MCAL_GPIO_Deinit
 * @brief 		- Reset all the GPIO Registers.
 * @param [in]   - GPIOx: where x can be (A..E depending on used device) to select the GPIO peripheral.
 * @retval 		- none
 * Note 			- none
================================================================**/
void MCAL_GPIO_DeInit(GPIO_TypeDef *GPIOx)
{
	if(GPIOx == GPIO_A)
	{
		RCC->RCC_APB2RSTR |= (1<<2);	// Bit 2 IOPARST: IO port A reset
		RCC->RCC_APB2RSTR &= ~ (1<<2);
	}
	else if(GPIOx == GPIO_B)
	{
		RCC->RCC_APB2RSTR |= (1<<3);	// Bit 3 IOPARST: IO port B reset
		RCC->RCC_APB2RSTR &= ~ (1<<3);
	}
	else if(GPIOx == GPIO_C)
	{
		RCC->RCC_APB2RSTR |= (1<<4);	// Bit 4 IOPARST: IO port C reset
		RCC->RCC_APB2RSTR &= ~ (1<<4);
	}
	else if(GPIOx == GPIO_D)
	{
		RCC->RCC_APB2RSTR |= (1<<5);	// Bit 5 IOPARST: IO port D reset
		RCC->RCC_APB2RSTR &= ~ (1<<5);
	}
	else if(GPIOx == GPIO_E)
	{
		RCC->RCC_APB2RSTR |= (1<<6);	// Bit 6 IOPARST: IO port E reset
		RCC->RCC_APB2RSTR &= ~ (1<<6);
	}
}

/**================================================================
 * @Fn 			- MCAL_GPIO_ReadPin
 * @brief 		- Read Specific PIN.
 * @param [in]   - GPIOx: where x can be (A..E depending on used device) to select the GPIO peripheral.
 * @param [in]   - PinNumber: Set Pin Number according @ref GPIO_PINS_define.
 * @retval 		- the input pin value (two values based on @ref GPIO_PIN_state)
 * Note 			- none
================================================================**/
uint8_t MCAL_GPIO_ReadPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	uint8_t bitstatus;
	if(((GPIOx->GPIO_IDR) & PinNumber) != (uint32_t) GPIO_PIN_RESET)
	{
		bitstatus = GPIO_PIN_SET;
	}
	else
	{
		bitstatus = GPIO_PIN_RESET;
	}
	return bitstatus;
}

/**================================================================
 * @Fn 			- MCAL_GPIO_ReadPort
 * @brief 		- Read Specific PORT.
 * @param [in]   - GPIOx: where x can be (A..E depending on used device) to select the GPIO peripheral.
 * @retval 		- the input port value
 * Note 			- none
================================================================**/
uint16_t MCAL_GPIO_ReadPort(GPIO_TypeDef *GPIOx)
{
	uint16_t port_status;
	port_status = (uint16_t)(GPIOx->GPIO_IDR);
	return port_status;
}

/**================================================================
 * @Fn 			- MCAL_GPIO_WritePin
 * @brief 		- Write on Specific PIN.
 * @param [in]   - GPIOx: where x can be (A..E depending on used device) to select the GPIO peripheral.
 * @param [in]   - PinNumber: specifies the port bit to read. Set by @ref GPIO_PINs_define
 * @param [in]   - value: PIN Value
 * @retval 		- none
 * Note 			- none
================================================================**/
void MCAL_GPIO_WritePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber, uint16_t value)
{
	if(value != GPIO_PIN_RESET)
	{
		// Bits 31:16 BRy: Port x Reset bit y (y= 0 .. 15)
		// These bits are write-only and can be accessed in Word mode only.
		// 0: No action on the corresponding ODRx bit
		// 1: Reset the corresponding ODRx bit
		// Note: If both BSx and BRx are set, BSx has priority.
		GPIOx->GPIO_BSRR = (uint32_t)PinNumber;
	}

	else
	{
		// Bits 15:0 BSy: Port x Set bit y (y= 0 .. 15)
		// These bits are write-only and can be accessed in Word mode only.
		// 0: No action on the corresponding ODRx bit
		// 1: Set the corresponding ODRx bit
		GPIOx->GPIO_BRR = (uint32_t)PinNumber;
	}

}

/**================================================================
 * @Fn 			- MCAL_GPIO_WritePort
 * @brief 		- Write on Specific PORT.
 * @param [in]   - GPIOx: where x can be (A..E depending on used device) to select the GPIO peripheral.
 * @param [in]   - value: Port Value
 * @retval 		- none
 * Note 			- none
================================================================**/
void MCAL_GPIO_WritePort(GPIO_TypeDef *GPIOx, uint16_t value)
{
	GPIOx->GPIO_ODR = (uint32_t)value;
}

/**================================================================
 * @Fn 			- MCAL_GPIO_TogglePin
 * @brief 		- Toggle Specific PIN.
 * @param [in]   - GPIOx: where x can be (A..E depending on used device) to select the GPIO peripheral.
 * @param [in]   - PinNumber: specifies the port bit to read. Set by @ref GPIO_PINs_define
 * @retval 		- none
 * Note 			- none
================================================================**/
void MCAL_GPIO_TogglePin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
	GPIOx->GPIO_ODR ^= (PinNumber);
}


/**================================================================
 * @Fn 			- MCAL_GPIO_LockPin
 * @brief 		- The locking mechanism allows the IO configuration to be frozen.
 * @param [in]   - GPIOx: where x can be (A..E depending on used device) to select the GPIO peripheral.
 * @param [in]   - PinNumber: specifies the port bit to read. Set by @ref GPIO_PINs_define
 * @retval 		- Ok if PIN Config is locked Or ERROR if pin is not locked (OK & ERROR are defined @ref GPIO_RETURN_LOCK)
 * Note 			- none
================================================================**/
uint8_t MCAL_GPIO_LockPin(GPIO_TypeDef *GPIOx, uint16_t PinNumber)
{
/*
 Bit 16
 LCKK[16]: Lock key
 This bit can be read anytime. It can only be modified using the Lock Key Writing Sequence.
 	 0: Port configuration lock key not active
 	 1: Port configuration lock key active. GPIOx_LCKR register is locked until the next reset.
 LOCK key writing sequence:
 	 Write 1
 	 Write 0
 	 Write 1
 	 Read 0
 	 Read 1 (this read is optional but confirms that the lock is active)
 Note: During the LOCK Key Writing sequence, the value of LCK[15:0] must not change.
 Any error in the lock sequence will abort the lock.

 Bits 15:0
 LCKy: Port x Lock bit y (y= 0 .. 15)
 These bits are read write but can only be written when the LCKK bit is 0.
 	 0: Port configuration not locked
 	 1: Port configuration locked.
*/

    // Set LCKK[16]
	volatile uint32_t tmp = 1<<16;
	// Set the LCKy
	tmp |= PinNumber;

	// Write 1
	GPIOx->GPIO_LCKR = tmp;
	// Write 0
	GPIOx->GPIO_LCKR = PinNumber;
	// Write 1
	GPIOx->GPIO_LCKR = tmp;

	// Read 0
	tmp = GPIOx->GPIO_LCKR;

	// Read 1 (this read is optional but confirms that the lock is active)
	if( (uint32_t) (GPIOx->GPIO_LCKR & 1<<16) )
	{
		return GPIO_RETURN_LOCK_Enabled;
	}
	else
	{
		return GPIO_RETURN_LOCK_Error;
	}
}


