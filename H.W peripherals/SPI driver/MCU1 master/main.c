/*
 * SPI.c
 *
 * Created: 7/23/2021 2:40:04 PM
 * Author : Shady mamdouh 
 */ 
#include "types.h"
#include "spi.h"
#include "register.h"

/*****************************************
*            MASTER 
****************************************/
int main(void)
{   
	uint8_t u8_DataSend;
	uint8_t u8_DataReceived;   // will not used
	/* SPI initialization */
	MCAL_SpiInit();
	u8_DataSend = 'A';
	/* transmit 'A' char ascii DEC : 65  Binary : 0b01000001  */
	MCAL_SPIMasterTXRX(&u8_DataSend,&u8_DataReceived);
    while (1) 
    {
		
		 
		
		
		
    }
}

