/*
 * MCU1 CARD.c
 *
 * Created: 7/30/2021 12:56:18 PM
 * Author : Shady Mamdouh 
 */ 
#include "APP/APP.h"
int main(void)
{
    APP_AppInit();
    while (1) 
    {
		
		APP_UpdateState();
    }
}

