/*
 * uartConfig.h
 *
 * Created: 7/19/2021 4:36:46 PM
 *  Author: Shady Mamdouh 
 */ 


#ifndef UARTCONFIG_H_
#define UARTCONFIG_H_

/********************Mode Selection*****************************
* select one of:
* USART_async
* USART_sync
*/
#define USART_MODE USART_async
/***************************************************************
* this selects the asynchronous speed(only in asynchronous modes)
* select one of:
* USART_async_normal
* USART_async_double
*/
#define ASYNC_SPEED USART_async_normal
/**************************************************************
* select the number of data bits
*USART_5_bit_char
*USART_6_bit_char
*USART_7_bit_char
*USART_8_bit_char
*USART_9_bit_char
*/
#define DATA_SIZE USART_8_bit_char
/**************************************************************
*USART_disable_parity
*USART_even_parity
*USART_odd_parity
*/
#define PARITY USART_disable_parity
/*************************************************************
*USART_1_stop_bit
*USART_2_stop_bits
*/
#define STOP_BITS USART_1_stop_bit
/************************************************************/
/* select BAUD rate and FOSC*/
#define USART_BAUD 4800ul
#define USART_FOSC 1000000ul
/*********************************************************/


#endif /* UARTCONFIG_H_ */