/*
 * SPI2.c
 *
 * Created: 7/23/2021 6:34:14 PM
 * Author : Shady mamdouh 
 */ 

#include "types.h"
#include "spi.h"
#include "register.h"
/******************************************************
				      SLAVE
*******************************************************/
int main(void)
{   
	uint8_t u8_DataSend;   // will not used
	uint8_t u8_DataReceived;   
	/* configure portc as output */
	DDRC =0XFF;
	/* SPI initialization */
	MCAL_SpiInit();
	
	/* slave trans receive */
	MCAL_SPISlaveTXRX(&u8_DataSend,&u8_DataReceived);
	
	/* display the received data */
	PORTC = u8_DataReceived;
    while (1) 
    {
		
		
		
    }
}


