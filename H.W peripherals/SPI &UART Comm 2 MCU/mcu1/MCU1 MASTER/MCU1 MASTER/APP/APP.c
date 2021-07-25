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
	/* counter */
	uint8_t u8_counter = 0;
	
	/* start receiving */
	USART_Receive(&aStringBuffer[u8_counter]);
	
	/* check ENTER Key is pressed that is an indicator to the end of string */
	while(aStringBuffer[u8_counter] != '\r')
	{
		u8_counter++;
		USART_Receive(&aStringBuffer[u8_counter]);
	}
	 /* ENTER key is pressed in the terminal */
	if (aStringBuffer[u8_counter] == '\r')
	{  
		/* close the string by adding null indicator */
		u8_counter++;
		aStringBuffer[u8_counter] = '\0';
	}
	
}
void APP_transmit(void)
{
	/* transmit the string from the terminal using SPI frequency fosc /128 */
	MCAL_SPIMasterTrans_String(aStringBuffer);
}
