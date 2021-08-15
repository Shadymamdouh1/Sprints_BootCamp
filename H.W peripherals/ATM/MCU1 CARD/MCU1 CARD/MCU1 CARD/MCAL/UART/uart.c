/*
 * uart.c
 *
 * Created: 7/19/2021 4:35:45 PM
 *  Author:Shady mamdouh 
 */ 
#include "register.h"
#include "types.h"
#include "uart.h"
#include "uartConfig.h"
/**********************UDRE interrupt request handler*****************************/
void __vector_14(void) __attribute__((signal,used));
/**********************************************************************************/

/**************************UDRE call back pointer to function********************************/
static void (*UDRE_CallBack)(void);
/******************************************************************************************/

/*******************Var to hold data to be transmitted using interrupt********************/
uint8_t U8_Transmit_UDR;
/******************************************************************************************/

/**********************RXC interrupt request handler*****************************/
void __vector_13(void) __attribute__((signal,used));
/**********************************************************************************/

/**************************RXC call back pointer to function********************************/
static void (*RXC_CallBack)(void);
/******************************************************************************************/

/*******************pointer to hold the location that will receive data using interrupt********************/
uint8_t *U8_Receive_UDR;
/******************************************************************************************/

UART_ERROR_t USART_Init(void)
{
	uint16_t u16_UBBR_VAL;
	
	
	/************BAUD RATE Configuration according to mode of operation*************/
	
	if ((USART_MODE ==USART_async)&&(ASYNC_SPEED==USART_async_normal)) // Normal Asynchronous mode
	{   
		u16_UBBR_VAL = ((USART_FOSC/(16 * USART_BAUD))-1);
		
		
		UCSRA &=~(1<<UCSRA_U2X);
		
		
	}
	else if ((USART_MODE ==USART_async)&&(ASYNC_SPEED==USART_async_double)) // Double speed Asynchronous mode
	{
		u16_UBBR_VAL = ((USART_FOSC/(8*USART_BAUD))-1);
		UCSRA |=(1<<UCSRA_U2X);
		//set_bit(UCSRA,UCSRA_U2X);
		
	}
	else if (USART_MODE ==USART_sync) // synchronous mode
	{
		u16_UBBR_VAL = (uint16_t)((USART_FOSC/(2*USART_BAUD))-1);
	}
	else /************************Configuration Error*****************/
	{
		return UART_WRONG_MODE_ERROR;
	}
	UBRRL = (uint8_t)u16_UBBR_VAL;
	UBBRH = (uint8_t)(u16_UBBR_VAL>>8);		
	/****************Set charachter size**********************************/
	if (DATA_SIZE==USART_9_bit_char)    //UCSZ2:0 ---> 111
	{
		//set_bit(UCSRB,UCSRB_UCSZ2);
		UCSRB |=(1<<UCSRB_UCSZ2);
		UCSRC |=(1<<UCSRC_URSEL)|(1<<UCSRC_UCSZ0)|(1<<UCSRC_UCSZ1);
	}
	else
	{
		UCSRC |=(1<<UCSRC_URSEL)|(DATA_SIZE<<UCSRC_UCSZ0);
	}
	/**************************parity mode******************************/
	UCSRC |=(1<<UCSRC_URSEL)|(PARITY<<UCSRC_UPM0);
	/*************************stop bits********************************/
	UCSRC |=(1<<UCSRC_URSEL)|(STOP_BITS<<UCSRC_USBS);
	/**************************synch or asynch mode****************************/

	UCSRC |=(1<<UCSRC_URSEL)|(USART_MODE<<UCSRC_UMSEL);
	/******************************************************************/

return UART_NO_ERROR;

}
UART_ERROR_t USART_Transmit(uint16_t u16_data)
{  
	//enable TX
	UCSRB |=(1<<UCSRB_TXEN);
	// waiting UDRE Flag
	while(!(UCSRA &(1<<UCSRA_UDRE)));
	if(DATA_SIZE==USART_9_bit_char)
	{
		UCSRB |=((u16_data>>8)&1);
	}
	UDR=(uint8_t)u16_data;
	return UART_NO_ERROR;
}
UART_ERROR_t USART_Transmit_Packet(uint8_t *pu8_data,uint8_t SIZE)
{
	uint8_t u8_counter;
	/************error handling*******************/
	if (pu8_data == 0)
	{
		return UART_INVALID_POINTER;
	}
	//enable TX
	UCSRB |=(1<<UCSRB_TXEN);
	for (u8_counter=0;u8_counter<SIZE;u8_counter++)
	{
		// waiting UDRE Flag
		while(!(UCSRA &(1<<UCSRA_UDRE)));
		UDR = *pu8_data;
		pu8_data++;
		
	}
	return UART_NO_ERROR;
	
}
UART_ERROR_t USART_receive_Packet(uint8_t *pu8_data,uint8_t u8_SIZE)
{
	uint8_t u8_counter;
	/**************ERROR***********************/
	if(pu8_data==0)
	{
		return UART_INVALID_POINTER;
	}
	//enable RX
	UCSRB |=(1<<UCSRB_RXEN);
	for (u8_counter=0;u8_counter<u8_SIZE;u8_counter++)
	{
		while(!(UCSRA &(1<<UCSRA_RXC)));
		*pu8_data =UDR;
		pu8_data++;
	}
	
	return UART_NO_ERROR;
	
}
 UART_ERROR_t USART_Receive (uint16_t *Ptr_to_val)
{
	if (Ptr_to_val == 0)
	{
		return UART_INVALID_POINTER;
	}
	//enable RX
	UCSRB |=(1<<UCSRB_RXEN);
	*Ptr_to_val=0; 
	while(!(UCSRA&(1<<UCSRA_RXC)));
	if(((UCSRA>>UCSRA_PE)&1)==0)    // if no parity error
	{
		if(DATA_SIZE==USART_9_bit_char)
		{
			*Ptr_to_val=(((UCSRB>>UCSRB_RXB8)&1)<<8);
		}
		*Ptr_to_val |=UDR;
		return UART_NO_ERROR; // NO ERROR
	}
	return UART_PARITY_ERROR;
}
UART_ERROR_t USART_Transmit_INTDriven(uint8_t *pu8_data,void (*ptr)(void))
{   
	//enable TX
	UCSRB |=(1<<UCSRB_TXEN);
	//data to be transmitted is copied to a global var to be loaded into UDR in the UDRE ISR
	U8_Transmit_UDR = *pu8_data;
	//call back function
	UDRE_CallBack=ptr;
	// Enable global interrupt
	SREG |=(1<<7);
	//enable UDRE interrupt
	USART_UDRInterruptEnable();
	
	return UART_NO_ERROR;
}
UART_ERROR_t USART_Receive_INTDriven(uint8_t *pu8_data,void (*ptr)(void))
{
	//enable RX
	UCSRB |=(1<<UCSRB_RXEN);
	//save the location of received data into a pointer 
	U8_Receive_UDR = pu8_data;
	//call back function
	RXC_CallBack = ptr;
	// Enable global interrupt
	SREG |=(1<<7);
	//enable RXC interrupt
	USART_RxInterruptEnable();
	
	return UART_NO_ERROR;
}
UART_ERROR_t USART_RxInterruptEnable(void)
{
	
	UCSRB |=(1<<UCSRB_RXCIE);
	return UART_NO_ERROR;
}
 UART_ERROR_t USART_RxInterruptDiable(void)
{
	
	UCSRB &=~(1<<UCSRB_RXCIE);
	return UART_NO_ERROR;
}
 UART_ERROR_t USART_TxInterruptEnable(void)
{
	
	UCSRB |=(1<<UCSRB_TXCIE);
	return UART_NO_ERROR;
}
 UART_ERROR_t USART_TxInterruptDisable(void)
{
	
	UCSRB &=~(1<<UCSRB_TXCIE);
	return UART_NO_ERROR;
}
 UART_ERROR_t USART_UDRInterruptEnable(void)
{
	
	UCSRB |=(1<<UCSRB_UDRIE);
	return UART_NO_ERROR;
}
 UART_ERROR_t USART_UDRInterruptDisable(void)
{
	
	UCSRB &=~(1<<UCSRB_UDRIE);
	return UART_NO_ERROR;
}
 UART_ERROR_t USART_TX_Enable(void)
{
	
	UCSRB |=(1<<UCSRB_TXEN);
	return UART_NO_ERROR;
}
 UART_ERROR_t USART_TX_Disable(void)
{
	UCSRB &=~(1<<UCSRB_TXEN);
	return UART_NO_ERROR;
}
UART_ERROR_t USART_RX_Enable(void)
{
	
	UCSRB |=(1<<UCSRB_RXEN);
	return UART_NO_ERROR;
}
UART_ERROR_t USART_RX_Disable(void)
{
	UCSRB &=~(1<<UCSRB_RXEN);
	return UART_NO_ERROR;
}
/************UDRE ISR***************************************************/
void __vector_14(void)
{
	//PORTA |=(1<<0);
	 UDR=U8_Transmit_UDR;
	USART_UDRInterruptDisable();
	UDRE_CallBack();
}
/**************************************/

/*************RXC ISR*******************/

void __vector_13(void)
{
	*U8_Receive_UDR =UDR;
	
	RXC_CallBack();
}
/*******************************************/