/*
 * MCU2 SLAVE.c
 *
 * Created: 7/25/2021 2:05:14 PM
 * Author : Shady Mamdouh 
 */ 

#include "APP/app.h"
/***********************************************
				SLAVE
**********************************************/

int main(void)
{
   
	APPInit();
    while (1) 
    {   
		/* get string from the master using SPI */
		 APPGetString();
	   /* transmit the string to the terminal using UART */	 
		 APP_transmit();
    }
}

