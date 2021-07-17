/*
 * car controller.c
 *
 * Created: 7/17/2021 12:57:08 AM
 * Author : Shady Mamdouh
 */ 

#include "APP.h"
int main(void)
{   
	
    App_init();
	
    while (1) 
    {   
		
		GetState();
		updateAPPState();
		
    }
}

