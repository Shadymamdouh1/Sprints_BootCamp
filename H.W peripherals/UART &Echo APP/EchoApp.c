/*
 * UART.c
 *
 * Created: 7/19/2021 4:32:31 PM
 * Author : Shady Mamdouh 
 */ 
#include "types.h"
#include "uart.h"
int main(void)
{  
	
	uint8_t str[14];
	USART_Init();
	
    while (1) 
    {    
		// this function using polling so it should receive the whole 14 characters before send them back
	   // receiving 14-charter string
		USART_receive_Packet(str,sizeof(str));
		// send it back
		USART_Transmit_Packet(str,sizeof(str));
	}

}