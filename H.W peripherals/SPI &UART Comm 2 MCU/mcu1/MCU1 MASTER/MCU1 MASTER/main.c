/*
 * MCU1 MASTER.c
 *
 * Created: 7/25/2021 12:58:36 PM
 * Author : Shady Mamdouh
 */ 

#include "APP/app.h"
/*************************************************************
					     MASTER
**************************************************************/
int main(void)
{
    APPInit();
	
    while (1) 
    {   
		/* Get the string from the terminal using UART baud rate 4800 */
		APPGetString();
		/* transmit the string to the slave using SPI frequency fosc /128 */
		APP_transmit();
    }
}

