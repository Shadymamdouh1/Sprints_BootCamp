/*
 * Thermostat.c
 *
 * Created: 8/3/2021 7:51:10 PM
 * Author : Shady Mmadouh
 */ 
#include "APP/types.h"
#include "APP/APP.h"

int main(void)
{   
	
    APP_APPInit();
    while (1) 
    {
		
		
		APP_GetState();
		APP_UpdateState();
		
    }
}

