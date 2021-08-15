/*
 * timer_Cfg.c
 *
 * Created: 7/14/2021 7:29:39 PM
 *  Author: Shady Mamdouh
 */
#include "timer.h"
 #include "timer_Cfg.h"

strGPt_config_t timer_config[CHANNELS_NUMBER] =
{
	{TIMER0,TIMER_OVF,NO_PRESCAIING},
	{TIMER1,TIMER_OVF,NO_PRESCAIING}	
} ;
