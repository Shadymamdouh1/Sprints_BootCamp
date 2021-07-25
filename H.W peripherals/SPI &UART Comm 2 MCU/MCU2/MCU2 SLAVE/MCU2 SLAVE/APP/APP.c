/*
 * APP.c
 *
 * Created: 7/25/2021 1:22:53 PM
 *  Author: Shady Mamdouh
 */ 
/**********Includes*******************/
#include "..\MCAL\UART\uart.h"
#include "..\MCAL\UART\uartConfig.h"
#include "..\MCAL\SPI\spi.h"
#include "..\MCAL\SPI\spiConfig.h"
#include "types.h"
#include "register.h"
/***************************************/
/**************string buffer*************/
uint8_t aStringBuffer[255];
/****************************************/
void APPInit(void)
{ 
	/* initialize the UART according to config file */
	USART_Init();
	/* initialize the SPI according to config file */
	MCAL_SpiInit();
}
/* get string from terminal using UART */
void APPGetString(void)
{
	/* we receive the string over SPI connection */
	MCAL_SPISlaveReceive_String(aStringBuffer);
}
void APP_transmit(void)
{
	uint8_t u8_counter =0;
	
	/* till the end of the string */
	while(aStringBuffer[u8_counter] != '\0')
	{
		USART_Transmit(aStringBuffer[u8_counter]);
		u8_counter++;
	}
	
}
