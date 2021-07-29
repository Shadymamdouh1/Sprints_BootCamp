/*
 * EEPROM MCU Interface.c
 *
 * Created: 7/29/2021 2:06:17 PM
 * Author : Shady Mamdouh
 */ 

#include "APP/APP.h"
int main(void)
{   
	
	APPInit();
    while (1) 
    {
		APP_GetState();
		APP_UpdateState();
    }
}

