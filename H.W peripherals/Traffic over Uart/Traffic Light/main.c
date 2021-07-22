/*
 * control MCU over UART.c
 *
 * Created: 7/21/2021 6:22:31 PM
 * Author : Shady Mamdouh
 */ 

#include "APP/Application.h"


int main(void)
{
    
	APP_init();
	
    while (1) 
    {
		APP_GetState();
		APP_UpdateState();
    }
}

