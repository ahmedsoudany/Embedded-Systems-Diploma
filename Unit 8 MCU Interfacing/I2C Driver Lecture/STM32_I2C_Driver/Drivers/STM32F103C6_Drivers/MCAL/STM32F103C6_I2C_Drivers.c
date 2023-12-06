/*
 * STM32F103C6_I2C_Drivers.c
 *
 *  Created on: Nov 19, 2023
 *      Author: LEGION
 */


#include "STM32F103C6_I2C_Drivers.h"

/*
* ==================================================================
*				 Generic Variables
* ==================================================================
*/
I2C_InitTypedef Global_I2C_Config[2] = {0};	;

/*
* ==================================================================
*				 Generic Macros
* ==================================================================
*/
#define I2C1_INDEX		0
#define I2C2_INDEX		1


/*
* ==================================================================
*				 APIs
* ==================================================================
*/


/**=======================================================================================
 * @Fn				-MCAL_I2C_Init
 * @brief			-Initializes the I2C acc. to the specifies parameters
 * @param [in]		-I2Cx: where x can be (1..3 depending on device used)
 * @param [in]		-I2C_InitStruct: ALL SPI Configuration EXTI_PinCfg_t
 * 					 the configuration information for the specified GPIO PIN
 * @retval		    -none
 * Note             -
 */
void MCAL_I2C_Init(I2C_TypeDef* I2Cx, I2C_InitTypedef* I2C_InitStruct)
{
	uint16_t tmpreg = 0 , freqrange = 0;
	uint32_t pclk1 = 8000000;
	uint32_t result = 0;
	//1- Enable RCC Clock
	if ( I2Cx == I2C1)
	{
		Global_I2C_Config[I2C1_INDEX] = *I2C_InitStruct;
		RCC_I2C1_CLK_EN();
	}
	else if ( I2Cx == I2C1)
	{
		Global_I2C_Config[I2C2_INDEX] = *I2C_InitStruct;
		RCC_I2C2_CLK_EN();
	}

	//2- Check Mode
	if ( I2C_InitStruct->I2C_Mode == I2C_Mode_I2C)
	{
		/*-------------------------- INIT Timing --------------------------*/

		//–-- I2C_CR2.FREQ[5:0]: Peripheral clock frequency
		/* Get the I2Cx CR2 Value */
		tmpreg = I2Cx->CR2;
		/* Clear frequency FREQ[5:0] bits */
		tmpreg &= ~(I2C_CR2_FREQ_Msk);
		/* Get pclk1 frequency value */
		pclk1 = MCAL_RCC_GetPCLK1Freq();
		/* Set frequency bits depending on pclk1 value */
		freqrange = (uint16_t) (pclk1 / 1000000) ;

		tmpreg |= freqrange ;
		/* Write to I2Cx CR2 */
		I2Cx->CR2 = tmpreg ;


		//• Configure the clock control registers (I2C_CCR)
		/* Disable the selected I2C peripheral to configure time */

		I2Cx->CR1 &= ~(I2C_CR1_PE);

		tmpreg = 0;

		/*Configure speed in standard mode */
		if ( (I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_50K) || (I2C_InitStruct->I2C_ClockSpeed == I2C_SCLK_SM_100K) )
		{
			/* Standard Mode speed calculate */

			//			Tclk/2 = CRR * Tpclk1
			//			CRR = Tclk /(2 * Tpclk1)
			//			CRR = Fpclk1 / (2 * I2C_ClockFrequency)

			result = (uint16_t)(pclk1 / ( I2C_InitStruct->I2C_ClockSpeed << 1) ) ;

			tmpreg |= result;

			I2Cx->CCR = tmpreg;




			/*-------------------------- I2C_TRISE Configuration --------------------------*/

			//			For instance: in Sm mode, the maximum allowed SCL rise time is 1000 ns.
			//			If, in the I2C_CR2 register, the value of FREQ[5:0] bits is equal to 0x08 and TPCLK1 = 125 ns
			//			therefore the TRISE[5:0] bits must be programmed with 09h.
			//			(1000 ns / 125 ns = 8 + 1)
			I2Cx->TRISE = freqrange + 1;
		}
		else
		{
			//			Fast Mode Not supported
		}

		/*-------------------------- I2Cx_CR1 Configuration --------------------------*/

		tmpreg = I2Cx->CR1 ;

		tmpreg |= (uint16_t)(I2C_InitStruct->I2C_ACK_Control | I2C_InitStruct->General_Call_Address_Detection | I2C_InitStruct->I2C_Mode | I2C_InitStruct->Stretch_Mode);

		/* Write to I2Cx CR1 */
		I2Cx->CR1 = tmpreg;

		/*-------------------------- I2Cx_OAR1 & I2Cx_OAR2 Configuration --------------------------*/
		tmpreg = 0;

		if(I2C_InitStruct->I2C_Slave_Address.Enable_Dual_ADD == 1)
		{
			tmpreg = I2C_OAR2_ENDUAL;
			tmpreg |= I2C_InitStruct->I2C_Slave_Address.Secondary_slave_address << I2C_OAR2_ENDUAL ;
			I2Cx->OAR2 = tmpreg;
		}

		tmpreg = 0;
		tmpreg |= I2C_InitStruct->I2C_Slave_Address.Primary_slave_address << 1;
		tmpreg |= I2C_InitStruct->I2C_Slave_Address.I2C_Addressing_Slave_Mode;
		I2Cx->OAR1 = tmpreg;


	}
	else if ( I2C_InitStruct->I2C_Mode == I2C_Mode_SMBus)
	{
		//SMBUS Not Supported
	}


	// interrupt Mode ==> Slave Mode
	// Check callback pointer != Null
	if(I2C_InitStruct->P_Slave_Event_CallBack != NULL) // that Enable Slave IRQ States Mode
	{
		I2Cx->CR2 |= ( I2C_CR2_ITERREN);
		I2Cx->CR2 |= ( I2C_CR2_ITEVTEN);
		I2Cx->CR2 |= ( I2C_CR2_ITBUFEN);

		if ( I2Cx == I2C1)
		{
			NVIC_IRQ31_I2C1_EV_Enable;
			NVIC_IRQ32_I2C1_ER_Enable;
		}
		else if ( I2Cx == I2C2)
		{
			NVIC_IRQ33_I2C2_EV_Enable;
			NVIC_IRQ34_I2C2_ER_Enable;
		}

		I2Cx->SR1 = 0;
		I2Cx->SR2 = 0;
	}

	/* Enable the selected I2C peripheral */
	I2Cx->CR1 |= I2C_CR1_PE;
}

/**=======================================================================================
 * @Fn				-MCAL_I2C_DeInit
 * @brief			-DeInitializes the I2C
 * @param [in]		-I2Cx: where x can be (1..3 depending on device used)
 * @retval		    -none
 * Note             -Reset the Model by RCC
 * */

void MCAL_I2C_DeInit(I2C_TypeDef* I2Cx)
{
	if ( I2Cx == I2C1)
	{
		NVIC_IRQ31_I2C1_EV_Disable;
		NVIC_IRQ32_I2C1_ER_Disable;
		RCC_I2C1_Reset();
	}
	else if ( I2Cx == I2C2)
	{
		NVIC_IRQ33_I2C2_EV_Disable;
		NVIC_IRQ34_I2C2_ER_Disable;
		RCC_I2C2_Reset();
	}

}
/**=======================================================================================
 * @Fn				-MCAL_I2C_GPIO_Set_Pins
 * @brief			-Initializes the GPIO Pins (
 * @param [in]		-I2Cx: where x can be (1..3 depending on device used)
 * @retval		    -none
 * Note             -Should Enable the corresponding ALT & GPIO in RCC clock Also called after MCAL_USART_Init()
 */
void MCAL_I2C_GPIO_Set_Pins(I2C_TypeDef* I2Cx)
	{
	GPIO_PinConfig_t PinCfg ;

	if ( I2Cx == I2C1)
		{
			//		PB6 : I2C1_SCL
			//		PB7 : I2C_SDA

		PinCfg.GPIO_PinNumber = GPIO_PIN_6;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_7;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		}
	else if ( I2Cx == I2C2)
	{
		//		PB10 : I2C1_SCL
		//		PB11 : I2C_SDA

		PinCfg.GPIO_PinNumber = GPIO_PIN_10;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);

		PinCfg.GPIO_PinNumber = GPIO_PIN_1;
		PinCfg.GPIO_MODE = GPIO_MODE_OUTPUT_AF_OD;
		PinCfg.GPIO_OUTPUT_SPEED = GPIO_SPEED_10M;
		MCAL_GPIO_Init(GPIOB, &PinCfg);
		}
}
/**=======================================================================================
 * @Fn				-MCAL_I2C_Master_TX
 * @brief			-Send Buffer on I2C
 * @param [in]		-I2Cx: where x can be (1..3 depending on device used)
 * @param [in]		-pTxBuffer Buffer
 * @param [in]		-PollingEn Enable pooling or disable it
 * @retval		    -none
 * Note             -
 */
void MCAL_I2C_Master_TX (I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataout,uint32_t datalen, Stop_Condition Stop, Repeated_Start Start)
{
	int i ;
	//todo
	//support timeout (configure timer working for specific duration rise interrupt
	//timer_interrupt() { flag = 1 }
	//so any code exist in while (check_flag || Any polling condition)
	// 1. Set the Start Bit in the I2C_CR1 register to generate a Start Condition
	I2C_GenerateSTART(I2Cx,ENABLE,Start);

	// 2. Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while( !(I2C_GetFlagStatus(I2Cx,EV5)) );

	// 3. Send Address
	I2C_SendAddres(I2Cx,devAddr,I2C_Direction_Transmitter); //Address

	// 4.wait EV6
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while( !(I2C_GetFlagStatus(I2Cx,EV6)) );

	// 5. /* TRA, BUSY, MSL, TXE flags */
	while( !(I2C_GetFlagStatus(I2Cx,MASTER_BYTE_TRANSMITTING)) );

	for(i = 0 ; i < datalen ; i++)
	{
		/* Write in the DR register the data to be sent */
		I2Cx->DR = dataout[i];
		//EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
		while( !(I2C_GetFlagStatus(I2Cx,EV8)) );
	}
	// 6. wait EV8_2
	//EV8_2: TxE=1, BTF = 1, Program Stop request. TxE and BTF are cleared by hardware by the Stop condition
	//while( !(I2C_GetFlagStatus(I2Cx,EV8_2) );

	if(Stop == With_Stop)
	{
		// 7. Send Stop Condition
		I2C_GenerateSTOP(I2Cx, ENABLE);
	}


}
/**=======================================================================================
 * @Fn				-MCAL_I2C_Master_RX
 * @brief			-Send Buffer on UART
 * @param [in]		-I2Cx: where x can be (1..3 depending on device used)
 * @param [in]		-pTxBuffer Buffer
 * @param [in]		-PollingEn Enable pooling or disable it
 * @retval		    -none
 * Note             -
 */
void MCAL_I2C_Master_RX (I2C_TypeDef* I2Cx, uint16_t devAddr, uint8_t* dataout,uint32_t datalen, Stop_Condition Stop, Repeated_Start Start)
{
	uint8_t index =	I2Cx == I2C1 ? I2C1_INDEX : I2C2_INDEX	;

	int i;
	// 1. Set the Start Bit in the I2C_CR1 register to generate a Start Condition
	I2C_GenerateSTART(I2Cx,ENABLE,Start);

	// 2. Wait for EV5
	// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
	while( !(I2C_GetFlagStatus(I2Cx,EV5)) );

	// 3. Send Address
	I2C_SendAddres(I2Cx,devAddr,I2C_Direction_Receiver); //Address

	// 4.wait EV6
	// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
	while( !(I2C_GetFlagStatus(I2Cx,EV6)) );

	I2C_AcknowledgeConfig(I2Cx,ENABLE);

	if(datalen)
	{
		for(i  = datalen ; i > 1 ; i--)
		{
			/* Wait until RXNE becomes 1 */
			while( !(I2C_GetFlagStatus(I2Cx,EV7)) );
			/* read the data from data register in to buffer */
			*dataout = I2Cx->DR;
			/* increment the buffer address */
			dataout++;

		}

	}

	I2C_AcknowledgeConfig(I2Cx,DISABLE);

	if(Stop == With_Stop)
		{
			// 7. Send Stop Condition
			I2C_GenerateSTOP(I2Cx, ENABLE);
		}

	//re-enable-Ack
		if(Global_I2C_Config[index].I2C_ACK_Control == I2C_ACK_Enable)
		{
			I2C_AcknowledgeConfig(I2Cx,ENABLE);
		}
}

/**=======================================================================================
 * @Fn				-MCAL_I2C_Master_TX
 * @brief			-Send Buffer on I2C
 * @param [in]		-I2Cx: where x can be (1..3 depending on device used)
 * @param [in]		-pTxBuffer Buffer
 * @param [in]		-PollingEn Enable pooling or disable it
 * @retval		    -none
 * Note             -
 */
void MCAL_I2C_SlaveSendData(I2C_TypeDef* I2Cx, uint8_t data)
{
	I2Cx->DR = data;
}
/**=======================================================================================
 * @Fn				-MCAL_I2C_Master_RX
 * @brief			-Send Buffer on UART
 * @param [in]		-I2Cx: where x can be (1..3 depending on device used)
 * @param [in]		-pTxBuffer Buffer
 * @param [in]		-PollingEn Enable pooling or disable it
 * @retval		    -none
 * Note             -
 */
uint8_t MCAL_I2C_SlaveReceiveData(I2C_TypeDef* I2Cx)
{
	return (uint8_t) I2Cx->DR;
}

void I2C_GenerateSTART(I2C_TypeDef* I2Cx, FunctionalState NewState, Repeated_Start Start)
{
	if ( Start != Repeated_start)
	{
		//Check if the Bus is idle
		while( I2C_GetFlagStatus(I2Cx,I2C_FLAG_BUSY) );
	}

//	Bit 8 START: Start generation
//	This bit is set and cleared by software and cleared by hardware when start is sent or PE=0.
//	In Master Mode:
//	0: No Start generation
//	1: Repeated start generation
//	In Slave mode:
//	0: No Start generation
//	1: Start generation when the bus is free

	if(NewState != DISABLE)
	{
		/* Generate a START condition */
		I2Cx->CR1 |= I2C_CR1_START;
	}
	else
	{
		/* Disable the START condition generation */
		I2Cx->CR1 &= ~(I2C_CR1_START) ;

	}
}

FlagStatus I2C_GetFlagStatus(I2C_TypeDef* I2Cx, Status Flag)
{
	volatile uint32_t dummyRead;
	FlagStatus bitstatus = RESET;
	uint32_t flag1 = 0 , flag2 = 0;
	uint32_t lastevent = 0 ;
	switch(Flag)
	{
		case I2C_FLAG_BUSY:
		{
			//		Bit 1 BUSY: Bus busy
			//		0: No communication on the bus
			//		1: Communication ongoing on the bus
			//		– Set by hardware on detection of SDA or SCL low
			//		– cleared by hardware on detection of a Stop condition.
			//		It indicates a communication in progress on the bus. This information is still updated when
			//		the interface is disabled (PE=0).
			if( (I2Cx->SR2) & (I2C_SR2_BUSY) )
			{
				bitstatus = SET;
			}
			else
			{
				bitstatus = RESET;
			}
			break;
		}
		case EV5:
		{
			// EV5: SB=1, cleared by reading SR1 register followed by writing DR register with Address.
			//			Bit 0 SB: Start bit (Master mode)
			//			0: No Start condition
			//			1: Start condition generated.
			//			– Set when a Start condition generated.
			//			– Cleared by software by reading the SR1 register followed by writing the DR register, or by
			//			hardware when PE=0
			if( (I2Cx->SR1) & (I2C_SR1_SB) )
			{
				bitstatus = SET;
			}
			else
			{
				bitstatus = RESET;
			}
			break;
		}
		case EV6:
		{
			// EV6: ADDR=1, cleared by reading SR1 register followed by reading SR2
			//			Bit 1 ADDR: Address sent (master mode)/matched (slave mode)
			//			This bit is cleared by software reading SR1 register followed reading SR2, or by hardware
			//			when PE=0.
			//			Address matched (Slave)
			//			0: Address mismatched or not received.
			//			1: Received address matched.
			//			– Set by hardware as soon as the received slave address matched with the OAR registers
			//			content or a general call or a SMBus Device Default Address or SMBus Host or SMBus Alert
			//			is recognized. (when enabled depending on configuration).
			if( (I2Cx->SR1) & (I2C_SR1_ADDR) )
			{
				bitstatus = SET;
			}
			else
			{
				bitstatus = RESET;
			}
			//to clear ADDR field : cleared by software reading SR1 register followed reading SR2
		//  	dummyRead = I2Cx->SR2;
			break;
		}
		case MASTER_BYTE_TRANSMITTING:
		{
			/* Read the I2Cx status register */
			flag1 = I2Cx->SR1;
			flag2 = I2Cx->SR2;
			flag2 = flag2 << 16;
			/* Get the last event value from I2C status register */
			lastevent = (flag1 | flag2) & ((uint32_t)0x00FFFFFF);
			if( (lastevent & Flag) == Flag )
			{
				/* SUCESS Last event is equal to I2C_EVENT */
				bitstatus = SET;
			}
			else
			{
				/* ERROR: Last event is different from I2C_EVENT */
				bitstatus = RESET;
			}
			//to clear ADDR field : cleared by software reading SR1 register followed reading SR2

			break;
		}
		case EV8:
		{
			//			EV8_1: TxE=1, shift register empty, data register empty, write Data1 in DR.
			//			Bit 7 TxE: Data register empty (transmitters)
			//			0: Data register not empty
			//			1: Data register empty
			//			– Set when DR is empty in transmission. TxE is not set during address phase.
			//			– Cleared by software writing to the DR register or by hardware after a start or a stop condition
			//			or when PE=0.
			//			TxE is not set if either a NACK is received, or if next byte to be transmitted is PEC (PEC=1)
			if( (I2Cx->SR1) & (I2C_SR1_TXE) )
			{
				bitstatus = SET;
			}
			else
			{
				bitstatus = RESET;
			}
			break;
		}
		case EV7:
		{
			//			Bit 6 RxNE: Data register not empty (receivers)
			//				0: Data register empty
			//				1: Data register not empty
			//				– Set when data register is not empty in receiver mode. RxNE is not set during address phase.
			//				– Cleared by software reading or writing the DR register or by hardware when PE=0.
			//				RxNE is not set in case of ARLO event.
			if( (I2Cx->SR1) & (I2C_SR1_RXNE) )
			{
				bitstatus = SET;
			}
			else
			{
				bitstatus = RESET;
			}
			break;
		}
	}


	return bitstatus;

}

void I2C_SendAddres(I2C_TypeDef* I2Cx, uint16_t Address, I2C_Direction Direction)
{
	uint8_t index =	I2Cx == I2C1 ? I2C1_INDEX : I2C2_INDEX	;

	if(Global_I2C_Config[index].I2C_Slave_Address.I2C_Addressing_Slave_Mode == I2C_Addressing_Slave_mode_7Bit)
	{

		Address = (Address << 1);

		if ( Direction != I2C_Direction_Transmitter)
		{
			/* Set the address bit0 for read */
			Address |= 1<<0;
		}
		else
		{
			/* Reset the address bit0 for write */
			Address &= ~(1<<0);
		}
	}
	else
	{
		//not supported for 10bit mode
	}

	I2Cx->DR = Address;
}

void I2C_GenerateSTOP(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
	if(NewState != DISABLE)
	{
		/* Generate a STOP condition */
		I2Cx->CR1 |= I2C_CR1_STOP;
	}
	else
	{
		/* Disable the STOP condition generation */
		I2Cx->CR1 &= ~(I2C_CR1_STOP) ;

	}
}
void I2C_AcknowledgeConfig(I2C_TypeDef* I2Cx, FunctionalState NewState)
{
	if(NewState != DISABLE)
		{
			/* Generate a ACK condition */
			I2Cx->CR1 |= I2C_CR1_ACK;
		}
		else
		{
			/* Disable the ACK condition generation */
			I2Cx->CR1 &= ~(I2C_CR1_ACK) ;
		}
}

void Slave_States(I2C_TypeDef* I2Cx, Slave_State State)
{
	uint8_t index =	I2Cx == I2C1 ? I2C1_INDEX : I2C2_INDEX	;

	switch(State)
	{

		case I2C_ERROR_AF:
		{

			if( (I2Cx->SR2) & (I2C_SR2_TRA) )
			{
				// Slave shouldn't send anything else
			}

			break;
		}
		case I2C_EV_STOP:
		{
			//Make sure that the slave is really in transmitter mode
			if( (I2Cx->SR2) & (I2C_SR2_TRA) )
			{
				//Notify APP that the Stop Condition is sent by the master
				Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_STOP);
			}

			break;
		}
		case I2C_EV_ADDR_Matched:
			{
					//Notify APP that the Stop Condition is sent by the master
					Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_ADDR_Matched);
			}
			break;

		case I2C_EV_Data_REQ:
			{
				//Make sure that the slave is really in transmitter mode
				if( (I2Cx->SR2) & (I2C_SR2_TRA) )
				{
					//the APP layer should send the data (MCAL_I2C_SlaveSendData ) in this state
					Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_Data_REQ);
				}

				break;
			}
		case I2C_EV_Data_RCV:
		{
			//Make sure that the slave is really in receiver mode
			if( (I2Cx->SR2) & (I2C_SR2_TRA) )
			{
				//the APP layer should read the data (MCAL_I2C_SlaveReceiveData ) in this state
				Global_I2C_Config[index].P_Slave_Event_CallBack(I2C_EV_Data_RCV);
			}

			break;
		}

	}



}

void I2C1_ER_IRQHandler(void)
{

}

void I2C1_EV_IRQHandler(void)
{
	volatile uint32_t dummy_read = 0;
	I2C_TypeDef* I2Cx = I2C1;
	/* Interrupt handling for both master and slave mode of a device */
	uint32_t temp1, temp2, temp3;

	temp1 = I2Cx->CR2 & ( I2C_CR2_ITEVTEN );
	temp2 = I2Cx->CR2 & ( I2C_CR2_ITBUFEN );
	temp3 = I2Cx->CR2 & ( I2C_SR1_STOPF );

	//Handle for interrupt generated by STOPE event
	//Note: Stop detection flag is applicable only slave mode
	if ( temp1 && temp3 )
	{
		//STOPF flag is set
		//Clear the STOPF ( i.e 1 ) read SR1 2) Write to CR1
		I2Cx->CR1 |= 0x0000;
		Slave_States(I2Cx, I2C_EV_STOP);
	}

	//-------------------------------------------------

	temp3 = I2Cx->SR1 & ( I2C_SR1_ADDR );
	//Handle for interrupt generated by the ADDR event
	//Note: When master mode : Address is sent
	//		When Slave mode  : Address matched with own address
	if ( temp1 && temp3 )
	{
		// Interrupt is generated because of ADDR event
		//Check for device mode
		if ( I2Cx->SR2 & ( I2C_SR2_MSL) )
		{
			//Master
		}
		else
		{
			//clear the ADDR flag ( read SR1 , read SR2 )
			dummy_read = I2Cx->SR1;
			dummy_read = I2Cx->SR2;
			Slave_States(I2Cx, I2C_EV_ADDR_Matched);
		}
	}

	//-------------------------------------------------

	temp3 = I2Cx->SR1 & ( I2C_SR1_TXE );
	//Handle for interrupt generated by the TXE event
	if ( temp1 && temp2 && temp3 )
	{

		//Check for device mode
		if ( I2Cx->SR2 & ( I2C_SR2_MSL) )
		{

		}
		else
		{
			//slave
			Slave_States(I2Cx, I2C_EV_Data_REQ);
		}
	}

	//-------------------------------------------------

	temp3 = I2Cx->SR1 & ( I2C_SR1_RXNE );
	//Handle for interrupt generated by SB = 1, cleared by reading SR1
	if ( temp1 && temp2 && temp3 )
	{

		//Check for device mode
		if ( I2Cx->SR2 & ( I2C_SR2_MSL) )
		{
			//The device is master
		}
		else
		{
			//slave
			Slave_States(I2Cx,I2C_EV_Data_RCV);
		}
	}
}



void I2C2_ER_IRQHandler(void)
{

}

void I2C2_EV_IRQHandler(void)
{

}
