/*
 * MCU2 ATM.c
 *
 * Created: 7/31/2021 12:11:47 PM
 * Author : Shady Madmouh
 */
#include "APP\types.h" 
#include "APP\APP.h"


			  

int main(void)
{
	APP_Init();
	
    while (1) 
    {
		APP_GetState();
		APP_UpdateState();
    }
}

