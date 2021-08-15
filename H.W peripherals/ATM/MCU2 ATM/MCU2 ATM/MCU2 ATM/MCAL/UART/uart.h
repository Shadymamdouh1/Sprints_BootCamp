/*
 * uart.h
 *
 * Created: 7/19/2021 4:36:01 PM
 *  Author: Shady mamdouh 
 */ 


#ifndef UART_H_
#define UART_H_
#include "types.h"
/**************** Registers bits**********************************/
#define UCSRA_RXC 7
#define UCSRA_TXC 6
#define UCSRA_UDRE 5
#define UCSRA_FE 4
#define UCSRA_DOR 3
#define UCSRA_PE 2
#define UCSRA_U2X 1
#define UCSRA_MPCM 0

#define UCSRB_RXCIE 7
#define UCSRB_TXCIE 6
#define UCSRB_UDRIE 5
#define UCSRB_RXEN 4
#define UCSRB_TXEN 3
#define UCSRB_UCSZ2 2
#define UCSRB_RXB8 1
#define UCSRB_TXB8 0

#define UCSRC_URSEL 7
#define UCSRC_UMSEL 6
#define UCSRC_UPM1 5
#define UCSRC_UPM0 4
#define UCSRC_USBS 3
#define UCSRC_UCSZ1 2
#define UCSRC_UCSZ0 1
#define UCSRC_UCPOL 0

/*********************operation modes*****************************/
enum USART_MOD    // asynchronous or synchronous  mode
{
	USART_async,
	USART_sync
};
/*************** asynchronous mode speed*************************/
enum USART_async_speed  // according to U2X bit
{
	USART_async_normal,
	USART_async_double
};
/************************data size******************************/
enum USART_Char_size   // number of data bits
{
	USART_5_bit_char,
	USART_6_bit_char,
	USART_7_bit_char,
	USART_8_bit_char,
	USART_9_bit_char
};
/*********************parity bits***********************************/
enum USART_Parity     // disable parity or enable with number of parity bits
{
	USART_disable_parity,
	reserved,
	USART_even_parity,
	USART_odd_parity
};
/*********************stop bits***************************************/
enum USART_Stop_bits // number of stop bits
{
	USART_1_stop_bit,
	USART_2_stop_bits
};
/************************Error handling******************************/
typedef enum UART_ERROR_t
{
	UART_NO_ERROR,
	UART_WRONG_MODE_ERROR,
	UART_INVALID_POINTER,
	UART_PARITY_ERROR
	}UART_ERROR_t;
/********************************************************************	
*                             APIs
*******************************************************************
* Name :			 USART_Init
* Description : initialize the uart module according to the configuration at uartConfig.h
*/
UART_ERROR_t USART_Init(void);
/***************************************************************************
* Name : USART_Transmit
* Description : this function is used to transmit 1 frame and it uses polling 
*               mechanism to transmit the data
*				it takes argument uint16_t to handle 9 bits data size configuration
*/
UART_ERROR_t USART_Transmit(uint16_t u16_data);
/**************************************************************************
* Name : USART_Receive
* Description : this function is used to receive 1 frame and it uses polling
*               mechanism to receive the data
*				it takes argument pointer to uint16_t to handle 9 bits data size configuration
*/
UART_ERROR_t USART_Receive (uint16_t *Ptr_to_val);
/*****************************************************************************
* Name : USART_Transmit_Packet
* Description : this function is used to transmit multi frames and it uses polling
*               mechanism to transmit the data
*				it takes an argument pointer to uint8_t array and the number of
*               frames or array size 
*/
UART_ERROR_t USART_Transmit_Packet(uint8_t *pu8_data,uint8_t SIZE);
/******************************************************************************
 Name : USART_receive_Packet
 * Description : this function is used to receive multi frames and it uses polling
 *               mechanism to transmit the data
 *				 it takes an argument pointer to uint8_t array that will hold data and the number of
 *               frames or array size
*/
UART_ERROR_t USART_receive_Packet(uint8_t *pu8_data,uint8_t u8_SIZE);
/******************************************************************************
Name : USART_Transmit_INTDriven
* Description : this function is used to transmit 1 frame and it uses interrupt
*               mechanism to transmit the data
*				it takes argument pointer to uint8_t and pointer to function
*               that will jump to after transmit
*/
UART_ERROR_t USART_Transmit_INTDriven(uint8_t *pu8_data,void (*ptr)(void));
/*******************************************************************************
Name : USART_Receive_INTDriven
* Description : this function is used to receive 1 frame and it uses interrupt
*               mechanism to receive the data
*				it takes argument pointer to uint8_t and pointer to function
*               that will jump to after receive
*/
UART_ERROR_t USART_Receive_INTDriven(uint8_t *pu8_data,void (*ptr)(void));
/*******************************************************************************
Name : USART_RxInterruptEnable
* Description : Enable RXC Interrupt
*/
UART_ERROR_t USART_RxInterruptEnable(void);
/*****************************************************************************
Name : USART_RxInterruptDiable
* Description : Disable RXC Interrupt
*/
UART_ERROR_t USART_RxInterruptDiable(void);
/****************************************************************************
Name : USART_UDRInterruptEnable
* Description : Enable UDRE Interrupt
*/
 UART_ERROR_t USART_UDRInterruptEnable(void);
/***************************************************************************
Name : USART_UDRInterruptDisable
* Description : Disable UDRE Interrupt
*/

UART_ERROR_t USART_UDRInterruptDisable(void);
/***************************************************************************
Name : USART_TX_Enable
* Description : Enable TX
*/
UART_ERROR_t USART_TX_Enable(void);
/***************************************************************************
Name : USART_TX_Disable
* Description : Disable TX
*/
UART_ERROR_t USART_TX_Disable(void);
/***************************************************************************
Name : USART_RX_Enable
* Description : Enable RX
*/
UART_ERROR_t USART_RX_Enable(void);
/***************************************************************************
Name : USART_RX_Disble
* Description : Disable RX
*/
UART_ERROR_t USART_RX_Disable(void);
/***************************************************************************/



#endif /* UART_H_ */