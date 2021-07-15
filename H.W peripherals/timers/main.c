/*
 * Timer Driver.c
 *
 * Created: 7/14/2021 7:09:45 PM
 * Author : Shady Mamdouh 
 */ 

#include "types.h"
#include "timer.h"
#include "register.h"

#define F_CPU 1000000UL
// Function that will be called after timer ISR ends
void func(void)
{
PORTA |=(1<<1);
}
int main(void)
{   //*********************************** testing timer********************************************/
	// enable global interrupt
	SREG |=(1<<7);
	//sei();
	
	timer_config.EN_channel  = TIMER0;
	timer_config.EN_Prescaler = NO_PRESCAIING;
	timer_config.EN_mode = TIMER_OVF;
	GptInit();
	DDRA |=(1<<0);
	DDRA |=(1<<1);
	
	//delay for 5 seconds using synchronous function delay 
	
		GptStart_Sync(TIMER0,5000000);
	
	PORTA=1;
	GptStop(TIMER0);
	// delay 5 seconds using interrupt and callback function 
	GptStart_aSync(TIMER0,5000000,func);
    
	
    while (1) 
    {   
		
    }
}

