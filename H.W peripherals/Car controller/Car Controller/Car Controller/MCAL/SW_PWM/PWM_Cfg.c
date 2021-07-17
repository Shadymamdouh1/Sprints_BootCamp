/*
 * PWM_Cfg.c
 *
 * Created: 7/15/2021 6:53:48 PM
 *  Author: Shady Mamdouh
 */ 
#include "types.h"
#include "SW_PWM.h"
strSWPwm_ChannelConfig_t SW_PWMChannels[2]=
{
	//           // PIN NUM
	{TIMER_CH_0 , PWM_CH_0},
	
	{TIMER_CH_1 , PWM_CH_1},
	
	
};