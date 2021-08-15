/*
 * interrupts.c
 *
 * Created: 8/7/2021 3:08:13 PM
 *  Author: Shady mamdouh 
 */ 
#include "Interrupts.h"
#include "register.h"
#include "types.h"

/*********************EXTI0 interrupt request handler*****************************/
void __vector_1(void) __attribute__((signal,used));
/**********************************************************************************/
/**************************EXTI0 CALL back pointer to function********************************/
static void (*EXTI0_CallBack)(void);
/******************************************************************************************/
void SetEXTI0CallBackFunction(void (*ptr)(void))
{
	EXTI0_CallBack = ptr;
}


void EXTI0_init(uint8_t trigger)
{
	switch(trigger)
	{
		case LOW_LEVEL :
		
		 // we need to set ISC01:00 TO 00
		MCUCR &=~(1<<ISC00);
		MCUCR &=~(1<<ISC01);
		
		break;
		case Any_logic :
		// we need to set ISC10:00 TO 01
		MCUCR |=(1<<ISC00);
		MCUCR &=~(1<<ISC01);
		break;
		
		case Failing :
		
		MCUCR &=~(1<<ISC00); // we need to set ISC10:00 TO 10
		MCUCR |=(1<<ISC01);
		break;
		
		case Rising :
		
		MCUCR |=(1<<ISC00); // we need to set ISC10:00 TO 11
		MCUCR |=(1<<ISC01);
		break;
	}
	
}

void EXTI0_Enable(void)
{
	SREG |=(1<<I); // enable global interrupt
	GICR|=(1<<INT0);  // Enable EXTINT0
}
void EXTI0_Disable(void)
{
	/* clear interrupt flag */
	GIFR |=(1<<6);
	GICR &=~(1<<INT0);  // Disable EXTINT0
}

/*************EXTI0 ISR*******************/

void __vector_1(void)
{
	EXTI0_CallBack();
}
/*******************************************/