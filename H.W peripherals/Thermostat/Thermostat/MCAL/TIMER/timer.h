/*
 * timer.h
 *
 * Created: 7/14/2021 7:28:07 PM
 *  Author: Shady mamdouh 
 */ 
#include "types.h"

#ifndef TIMER_H_
#define TIMER_H_
/********************* PINS Macros********************************/
#define TCCR0_CS00 0
#define TCCR0_CS01 1
#define TCCR0_CS02 2
#define TCCR0_WGM01 3
#define TCCR0_COM00 4
#define TCCR0_COM01 5
#define TCCR0_WGM00 6
#define TCCR0_FOC0 7
#define TIFR_TOV0 0
#define TIMSK_TOIE0 0
#define TIMSK_OCIE0 1

#define TIFR_TOV0 0
#define TIFR_OCF0 1
//*********************** Enums************************/
/*********************** TIMER MODES******************/
typedef enum{
	TIMER_OVF,
	TIMER_CTC,
	TIMER_PWM_PhaseCorrect,
	TIMER_PWM_Fast
}TIMER_Mode;
//********************* TIMER CHANNEL****************/
 typedef enum{   
	TIMER0,
	TIMER1,
	TIMER2
	
}EN_TIMER_channel;
//********************PRE SCALE FACTOR**************/
 typedef enum TIMER_pre_scale{
	NO_CLK_SRC,  // timer disabled
	NO_PRESCAIING,
	PRESCAIING_CLK8,
	PRESCAIING_CLK64,
	PRESCAIING_CLK256,
	PRESCAIING_CLK1024,
	EXT_CLK_FALLING,
	EXT_CLK_RISING
} TIMER_pre_scale;
/**************************CONFIGURATION STRUCTURE************/
typedef struct{   
	 EN_TIMER_channel EN_channel;
	 TIMER_Mode EN_mode ;
	 TIMER_pre_scale EN_Prescaler;
	 
}strGPt_config_t;

#define CHANNELS_NUMBER 2

typedef void (*pfGpt_CallBack_t)(void);
/************************** ERROR HNADLER***************************/
typedef enum enuGpt_Status_t
{
	GPT_STATUS_ERROR_NOK,
	GPT_STATUS_ERROR_OK
}enuGpt_Status_t;

/********************************APIs*********************************/

/************************************************************************
 * Name : GptInit
 * used when we need to initialize specific timer channel
 * it takes its data from the global configuration structure timer_config
 */
enuGpt_Status_t GptInit(void); 
/***********************************************************************/


/***********************************************************************/
/*
* Name :GptStart_Sync
* function type : synchronous that freezes the system until finishes
* Used to generate delay depending on the previous configuration structure
* it uses timer overflow mode and polling mechanism
*it takes channel number and number of ticks 
*EX :GptStart_Sync(TIMER0,5000000); 
*note the time delay depends on the  configuration structure
*/
enuGpt_Status_t GptStart_Sync(uint8_t ChannelId, uint32_t u32_Ticks);
/****************************************************************************/


/****************************************************************************/
/*
* Name :GptStart_aSync
* function type : Asynchronous that uses interrupts and callback function
* Used to generate delay depending on the previous configuration structure
* it uses timer overflow mode and interrupt mechanism
*it takes channel number and number of ticks and the function name wanted to be called after the time ends
*EX :GptStart_aSync(TIMER0,5000000,func);
*note the time delay depends on the  configuration structure
*/
enuGpt_Status_t GptStart_aSync(uint8_t ChannelId, uint32_t u32_Ticks, pfGpt_CallBack_t CallBack);


/******************************************************************************/

/****************************************************************************/
/*
* Name :GptStop
* 
* Used to disable a specific timer channel according to its ID 
* it also clear counter and timer registers 
*/
enuGpt_Status_t GptStop(uint8_t ChannelId); 

/****************************************************************************/


#endif /* TIMER_H_ */