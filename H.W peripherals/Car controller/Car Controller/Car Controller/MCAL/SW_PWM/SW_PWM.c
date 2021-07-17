/*
 * SW_PWM.c
 *
 * Created: 7/15/2021 3:31:58 PM
 *  Author: Shady Mamdouh 
 */ 
#include "types.h"
#include "..\DIO\Dio.h"
#include "..\Timer\timer.h"
#include "SW_PWM.h"
#include "register.h"
#define ON_STATE 0
#define OFF_STATE 1

extern strSWPwm_ChannelConfig_t SW_PWMChannels[2];


enuSWPwm_Status_t SWPwm_Init(void)
{   
	// port A pin0 for PWM control speed for right motor
	strDio_pins[0].u8_PortNum=PORT_A;
	strDio_pins[0].u8_PinNum=PIN_0;
	strDio_pins[0].u8_Direction=DIO_PIN_DIR_OUTPUT;
	strDio_pins[0].u8_InitState=PIN_LOW;
	Dio_init(&strDio_pins[0]);
	
	// port A pin3 for PWM control speed for left motor
	strDio_pins[3].u8_PortNum=PORT_A;
	strDio_pins[3].u8_PinNum=PIN_0;
	strDio_pins[3].u8_Direction=DIO_PIN_DIR_OUTPUT;
	strDio_pins[3].u8_InitState=PIN_LOW;
	Dio_init(&strDio_pins[0]);
	
	// timer init
	timer_config.EN_channel=TIMER0;
	timer_config.EN_mode=TIMER_OVF;
	timer_config.EN_Prescaler=PRESCAIING_CLK64;				//		
	GptInit();
}


void SW_PWM_Wave0(void)
{  
	
	
	if (channel0_data.prevoius==ON_STATE)
	{    
		
		
		channel0_data.prevoius=OFF_STATE;
		Dio_writePin(SW_PWMChannels[0].u8_DioChannelID,PIN_LOW);
		GptStart_aSync(SW_PWMChannels[0].u8_GptChannelID,channel0_data.Ticks_OFF ,SW_PWM_Wave0);
		
	}
	else if (channel0_data.prevoius==OFF_STATE)
	{
		channel0_data.prevoius=ON_STATE;
		Dio_writePin(SW_PWMChannels[0].u8_DioChannelID,PIN_HIGH);
		GptStart_aSync(SW_PWMChannels[0].u8_GptChannelID,channel0_data.Ticks_ON ,SW_PWM_Wave0);
	}
	
}

enuSWPwm_Status_t SWPwm_Start(strSWPwm_ChannelConfig_t u8_ChannelID, uint32_t u32_Freq, uint8_t u8_DutyCycle)
{    
	
	uint32_t timer_freq= (1000000/64); //15625
	
	float  total_ticks =(timer_freq/u32_Freq); // 
	
	uint32_t Ticks_ON =(uint32_t)((u8_DutyCycle/100.0)*total_ticks);   // 
	uint32_t Ticks_OFF=(uint32_t)(((100-u8_DutyCycle)/100.0)*total_ticks); // 
	
	
	// data will be used in wave function
	channel0_data.Ticks_ON=Ticks_ON;
	channel0_data.Ticks_OFF=Ticks_OFF;
	channel0_data.prevoius=ON_STATE;
	GptStart_aSync(u8_ChannelID.u8_GptChannelID,Ticks_ON,SW_PWM_Wave0);
	
	Dio_writePin(SW_PWMChannels[0].u8_DioChannelID,PIN_HIGH);
}
enuSWPwm_Status_t SWPwm_Stop(strSWPwm_ChannelConfig_t u8_ChannelID)
{
	GptStop(u8_ChannelID.u8_GptChannelID);
	Dio_writePin(u8_ChannelID.u8_DioChannelID,PIN_LOW);
	
}