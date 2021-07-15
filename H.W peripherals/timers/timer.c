/*
 * timer.c
 *
 * Created: 7/14/2021 7:27:52 PM
 *  Author: Shady Mamdouh
 */ 
#include "types.h"
#include "timer.h"
#include "register.h"
//*************** interrupt request handler for Timer0 OVF ***************************/
void __vector_11(void) __attribute__((signal,used));


//********************* call back pointer to function**********************/
static void (*OVF_CallBack)(void);
//*************** number of iterations inside Timer OVF ISR**************/
volatile uint32_t u8_gOVF_Counter =0 ;
/******************************************************/

/*********************************************************************/
enuGpt_Status_t GptInit(void)
{   
	if(timer_config.EN_channel==TIMER0)
	{
		
	
	TCNT0= 0;
	// normal mode
	// clr WGM01 and WGM00
	TCNT0 &=~(1<<TCCR0_WGM00);
	TCNT0 &=~(1<<TCCR0_WGM01);
	}
}
/***********************************************************************/

/************************************************************************/
enuGpt_Status_t GptStart_Sync(uint8_t ChannelId, uint32_t u32_Ticks)
{   
	uint32_t counter;
	uint32_t u32_OVF_NUM=0;
	if (u32_Ticks<256)
	{
		TCNT0 = 256-u32_Ticks;
	}
	else
	{  
		u32_OVF_NUM = u32_Ticks / 256;
	    TCNT0 =256 - ( u32_Ticks % 256);
	}
	
	//clr pre scaler  bit field
      TCCR0 &=~(0b111<<TCCR0_CS00);
	  // set pre scaler
	  TCCR0 |=( timer_config.EN_Prescaler << TCCR0_CS00);
	  // number of overflow iteration to reach the ticks number
	for(counter=0;counter<=(u32_OVF_NUM+1);counter++)
	{
      // waiting flag OVF0
	while(! (  (TIFR & (1<<TIFR_TOV0)  ) >> TIFR_TOV0) );
		//clear flag
		TIFR |=(1<<TIFR_TOV0);
	}
}
//***************************************************************************/

/************************************************************************************************/
enuGpt_Status_t GptStart_aSync(uint8_t ChannelId, uint32_t u32_Ticks, pfGpt_CallBack_t CallBack)
{
	// interrupt enable
	TIMSK |=(1<<TIMSK_TOIE0);
	// assigning function to callback overflow pointer
	OVF_CallBack = CallBack;
	
	if (u32_Ticks<256)
	{
		TCNT0 = 256-u32_Ticks;
	}
	else
	{
		u8_gOVF_Counter = u32_Ticks / 256;
		TCNT0 =256 - ( u32_Ticks % 256);
	}
	
	
	//clr bit field
	TCCR0 &=~(0b111<<TCCR0_CS00);
	// set pre scaler
	TCCR0 |=( timer_config.EN_Prescaler<< TCCR0_CS00);
}
/*********************************************************************************/
enuGpt_Status_t GptStop(uint8_t ChannelId)
{
	//clr bit field disable timer pre scaler 0
	TCCR0 &=~(0b111<<TCCR0_CS00);
	//clr counter
	TCNT0 =0;
	// disable interrupt 
	TIMSK &=~(1<<TIMSK_TOIE0);
}
/***********************************************************************************/

/*********************** timer0 Overflow ISR************************************/
void __vector_11(void)
{   
	u8_gOVF_Counter--;
	
	if(u8_gOVF_Counter==0)
	{   
		// disable interrupt
		TIMSK &=~(1<<TIMSK_TOIE0);
		// call back
		OVF_CallBack();
	}
	
	
}
/**********************************************************************************/