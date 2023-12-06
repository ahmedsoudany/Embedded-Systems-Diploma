/*
 * STM32F103C6_SPI_Drivers.c
 *
 *  Created on: Nov 16, 2023
 *      Author: LEGION
 */



#include "STM32F103C6_SPI_Drivers.h"
/*
* ==================================================================
*				 Generic Variables
* ==================================================================
*/

SPI_Config* Global_SPI_Config[2] = {NULL,NULL};
/*
* ==================================================================
*				 Generic Macros
* ==================================================================
*/
#define SPI1_INDEX 	0
#define SPI2_INDEX 	1

/*
* ==================================================================
*				 Generic Function
* ==================================================================
*/


/*
* ==================================================================
*				 APIs
* ==================================================================
*/

/**=======================================================================================
 * @Fn				-MCAL_SPI_Init
 * @brief			-Initializes the SPI acc. to the specifies parameters
 * @param [in]		-SPIx: where x can be (1..3 depending on device used)
 * @param [in]		-SPI_Config: ALL SPI Configuration EXTI_PinCfg_t
 * 					 the configuration information for the specified GPIO PIN
 * @retval		    -none
 * Note             -Support for SPI Full Duplex Master/Slave only & NSS HW/SW
 * 					-in case of master you have to configure pin and drive it
 */

void MCAL_SPI_Init(SPI_TypeDef* SPIx,SPI_Config* SPI_Config)
{
	//Safety for registers
	uint16_t tmpreg_CR1 = 0;
	uint16_t tmpreg_CR2 = 0;

	if(SPIx == SPI1)
	{
		Global_SPI_Config[SPI1_INDEX] = SPI_Config;
		RCC_SPI1_CLK_EN();
	}
	else if(SPIx == SPI2)
	{
		Global_SPI_Config[SPI2_INDEX] = SPI_Config;
		RCC_SPI2_CLK_EN();
	}

	//Enable SPI CR1:Bit 6 SPE: SPI enable
	tmpreg_CR1 |= (0x1U << 6);

	//Master or Slave
	tmpreg_CR1 |=  SPI_Config->Device_Mode;

	//SPI-Communication_Mode
	tmpreg_CR1 |=  SPI_Config->Communication_Mode;

	//SPI_Frame_Format
	tmpreg_CR1 |= SPI_Config->DataSize;

	//SPI_Clock_Polarity
	tmpreg_CR1 |= SPI_Config->CLKPolartity;

	//SPI_Clock_Phase
	tmpreg_CR1 |= SPI_Config->CLKPhase;

	/* ===================NSS=============================== */
	if(SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_enable)
	{
		tmpreg_CR2 |= SPI_Config->NSS;
	}
	else if (SPI_Config->NSS == SPI_NSS_Hard_Master_SS_output_disable)
	{
		tmpreg_CR2 &= SPI_Config->NSS;
	}
	else
	{
		tmpreg_CR1 |= SPI_Config->NSS;
	}

//================================================================
	//SPI_BAUDRATRPRESCALER
	tmpreg_CR1 |= SPI_Config->SPI_BAUDRATEPRESCALAR;

	if(SPI_Config->IRQ_Enable != SPI_IRQ_Enable_NONE)
	{
		// SPI_IRQ_Enable_define
		tmpreg_CR2 |= SPI_Config->IRQ_Enable;

		if(SPIx == SPI1)
		{
			NVIC_IRQ35_SPI1_Enable;
		}
		else if(SPIx == SPI2)
		{
			NVIC_IRQ36_SPI2_Enable;
		}
	}

	SPIx->CR1 = tmpreg_CR1;
	SPIx->CR2 = tmpreg_CR2;

}
/**=======================================================================================
 * @Fn				-MCAL_SPI_DeInit
 * @brief			-DeInitializes the UART (Supported features ASYNCH. ONLY)
 * @param [in]		-USARTx: where x can be (1..3 depending on device used)
 * @param [in]		-UART_Config: ALL UART Configuration EXTI_PinCfg_t
 * 					 the configuration information for the specified GPIO PIN
 * @retval		    -none
 * Note             -Reset the Model by RCC
 */
void MCAL_SPI_DeInit(SPI_TypeDef* SPIx)
{
	if(SPIx == SPI1)
	{
		NVIC_IRQ35_SPI1_Disable;
		RCC_SPI1_Reset();
	}
	else if(SPIx == SPI2)
	{
		NVIC_IRQ36_SPI2_Disable;
		RCC_SPI2_Reset();
	}
}




/**=======================================================================================
 * @Fn				-MCAL_SPI_SendData
 * @brief			-Send Buffer on UART
 * @param [in]		-USARTx: where x can be (1..3 depending on device used)
 * @param [in]		-pTxBuffer Buffer
 * @param [in]		-PollingEn Enable pooling or disable it
 * @retval		    -none
 * Note             -Should initialize UART First
 * 					 //	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
					 //	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
					 //	because it is replaced by the parity.
					 //	When receiving with the parity enabled, the value read in the MSB bit is the received parity
					 //	bit.
 */

#define SPI_SR_TXE			((uint8_t)0x02)		/*! < Transmit buffer  Empty */
#define SPI_SR_RXEN			((uint8_t)0x01)		/*! < Transmit buffer  Not Empty */

void MCAL_SPI_SendData(SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum Polling_mechanism PollingEn)
{
	//TODO receive only

	if(PollingEn == PollingEnable)
		while(!((SPIx)->SR & SPI_SR_TXE));

	SPIx->DR = *pTxBuffer;
}
/**=======================================================================================
 * @Fn				-MCAL_SPI_ReceiveData
 * @brief			-Send Buffer on UART
 * @param [in]		-USARTx: where x can be (1..3 depending on device used)
 * @param [in]		-pTxBuffer Buffer
 * @param [in]		-PollingEn Enable pooling or disable it
 * @retval		    -none
 * Note             -Should initialize UART First
 * 					 //	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
					 //	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
					 //	because it is replaced by the parity.
					 //	When receiving with the parity enabled, the value read in the MSB bit is the received parity
					 //	bit.
 */



void MCAL_SPI_ReceiveData(SPI_TypeDef *SPIx, uint16_t *pRxBuffer, enum Polling_mechanism PollingEn)
{
	if(PollingEn == PollingEnable)
				while(!((SPIx)->SR & SPI_SR_TXE));

		*pRxBuffer = SPIx->DR ;
}
/**=======================================================================================
 * @Fn				-MCAL_SPI_TX_RX
 * @brief			-Send Buffer on UART
 * @param [in]		-USARTx: where x can be (1..3 depending on device used)
 * @param [in]		-pTxBuffer Buffer
 * @param [in]		-PollingEn Enable pooling or disable it
 * @retval		    -none
 * Note             -Should initialize UART First
 * 					 //	When transmitting with the parity enabled (PCE bit set to 1 in the USART_CR1 register),
					 //	the value written in the MSB (bit 7 or bit 8 depending on the data length) has no effect
					 //	because it is replaced by the parity.
					 //	When receiving with the parity enabled, the value read in the MSB bit is the received parity
					 //	bit.
 */
void MCAL_SPI_TX_RX(SPI_TypeDef *SPIx, uint16_t *pTxBuffer, enum Polling_mechanism PollingEn)
{

	if(PollingEn == PollingEnable)
		while(!((SPIx)->SR & SPI_SR_TXE));
	SPIx->DR = *pTxBuffer;

	if(PollingEn == PollingEnable)
		while(!((SPIx)->SR & SPI_SR_TXE));
	*pTxBuffer = SPIx->DR ;

}

/**=======================================================================================
 * @Fn				-MCAL_SPI_GPIO_Set_Pins
 * @brief			-Initializes the GPIO Pins (
 * @param [in]		-USARTx: where x can be (1..3 depending on device used)
 * @retval		    -none
 * Note             -Should Enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_USART_Init()
 */
void MCAL_SPI_GPIO_Set_Pins(SPI_TypeDef* SPIx)
{
	GPIO_PinConfig_t PinCfg;

	if(SPIx == SPI1)
	{
		//		PA4 : SPI1_NSS
		//		PA5 : SPI1_CLK
		//		PA6 : SPI1_MISO
		//		PA7 : SPI1_MOSI
		if(Global_SPI_Config[SPI1_INDEX]->Device_Mode == SPI_Device_Mode_MASTER)
		{
			//PA4 : SPI1_NSS
			switch(Global_SPI_Config[SPI1_INDEX]->NSS)
			{
			case SPI_NSS_Hard_Master_SS_output_disable:
				//Hardware master / salve Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;
			case SPI_NSS_Hard_Master_SS_output_enable:
				//Hardware master / salve Output enabled Alternate function
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
				break;
			}

			//		PA5 : SPI1_CLK
			//		Master Alternate function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//		PA6 : SPI1_MISO (supported only full duplex)
			//		Full duplex / master Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//todo to support half duplex and simplex

			//		PA7 : SPI1_MOSI
			//		Full duplex / master Alternate Function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

		}
		else //Slave
		{
			//PA4 : SPI1_NSS
			if (Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
			{
				//Hardware master/slave input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_4;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOA, &PinCfg);
			}
			//		PA5 : SPI1_CLK
			//		Slve Input floating
			PinCfg.GPIO_PinNumber = GPIO_PIN_5;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//		PA6 : SPI1_MISO (supported only full duplex)
			//		Full duplex / master (point to point) Alternate function  push-pull
			//		todo duplex/slave (multi-slave) Alternate function  push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_6;
			PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
			PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
			MCAL_GPIO_Init(GPIOA, &PinCfg);

			//todo to support half duplex and simplex

			//		PA7 : SPI1_MOSI
			//		Full duplex / master Alternate Function push-pull
			PinCfg.GPIO_PinNumber = GPIO_PIN_7;
			PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
			MCAL_GPIO_Init(GPIOA, &PinCfg);
		}
	}

	else if (SPIx == SPI2)
	{
		//		PB12 : SPI2_NSS
		//		PB13 : SPI2_CLK
		//		PB14 : SPI2_MISO
		//		PB15 : SPI2_MOSI
		{
			if(Global_SPI_Config[SPI2_INDEX]->Device_Mode == SPI_Device_Mode_MASTER)
			{
				//PB12 : SPI1_NSS
				switch(Global_SPI_Config[SPI2_INDEX]->NSS)
				{
				case SPI_NSS_Hard_Master_SS_output_disable:
					//Hardware master / salve Input floating
					PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
					MCAL_GPIO_Init(GPIOB, &PinCfg);
					break;
				case SPI_NSS_Hard_Master_SS_output_enable:
					//Hardware master / salve Output enabled Alternate function
					PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
					PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
					MCAL_GPIO_Init(GPIOB, &PinCfg);
					break;
				}

				//		PB13 : SPI1_CLK
				//		Master Alternate function push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_13;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

				//		PB14 : SPI1_MISO (supported only full duplex)
				//		Full duplex / master Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_14;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

				//todo to support half duplex and simplex

				//		PB15 : SPI1_MOSI
				//		Full duplex / master Alternate Function push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_15;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

			}
			else //Slave
			{
				//PB12 : SPI1_NSS
				if (Global_SPI_Config[SPI1_INDEX]->NSS == SPI_NSS_Hard_Slave)
				{
					//Hardware master/slave input floating
					PinCfg.GPIO_PinNumber = GPIO_PIN_12;
					PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
					MCAL_GPIO_Init(GPIOB, &PinCfg);
				}
				//		PB13 : SPI1_CLK
				//		Slve Input floating
				PinCfg.GPIO_PinNumber = GPIO_PIN_13;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

				//		PB14 : SPI1_MISO (supported only full duplex)
				//		Full duplex / master (point to point) Alternate function  push-pull
				//		todo duplex/slave (multi-slave) Alternate function  push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_14;
				PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_PP;
				PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
				MCAL_GPIO_Init(GPIOB, &PinCfg);

				//todo to support half duplex and simplex

				//		PB15 : SPI1_MOSI
				//		Full duplex / master Alternate Function push-pull
				PinCfg.GPIO_PinNumber = GPIO_PIN_14;
				PinCfg.GPIO_MODE = GPIO_MODE_INPUT_FLO;
				MCAL_GPIO_Init(GPIOB, &PinCfg);
			}
		}

	}

}


/*
* ==================================================================
*				 IRQ
* ==================================================================
*/


void SPI1_IRQHandler(void)
{
	struct S_IRQ_SRC irq_scr;

	irq_scr.TXE  = ( ( SPI1->SR & (1<<1)) >> 1);
	irq_scr.RXNE = ( ( SPI1->SR & (1<<0)) >> 0);
	irq_scr.ERRI = ( ( SPI1->SR & (1<<4)) >> 4);

	Global_SPI_Config[SPI1_INDEX]->P_IRQ_CallBack(irq_scr);
}
void SPI2_IRQHandler(void)
{
	struct S_IRQ_SRC irq_scr;

	irq_scr.TXE  = ( ( SPI2->SR & (1<<1)) >> 1);
	irq_scr.RXNE = ( ( SPI2->SR & (1<<0)) >> 0);
	irq_scr.ERRI = ( ( SPI2->SR & (1<<4)) >> 4);

	Global_SPI_Config[SPI2_INDEX]->P_IRQ_CallBack(irq_scr);
}


