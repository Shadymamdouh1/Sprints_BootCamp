/*
 * LED.c
 *
 * Created: 7/21/2021 6:31:56 PM
 *  Author: Shady mamdouh 
 */ 
/****************INCLUDES********************/
#include "..\..\MCAL\Dio\Dio.h"
#include "..\..\MCAL\Dio\Dio_Cfg.h"
#include "LED.h"
/********************************************/

void ECUAL_LedInit(void)
{  
	/* initialize Dio pins according to DioCfg.c  */
	Dio_init(&strDio_pins);
}

void ECUAL_GreenSignON(void)
{
	Dio_writePin(PIN_0,PIN_HIGH);
}

void ECUAL_GreenSignOFF(void)
{
	Dio_writePin(PIN_0,PIN_LOW);
}

void ECUAL_YellowSignON(void)
{
	Dio_writePin(PIN_1,PIN_HIGH);
}

void ECUAL_YellowSignOFF(void)
{
	Dio_writePin(PIN_1,PIN_LOW);
}

void ECUAL_RedSignON(void)
{
	Dio_writePin(PIN_2,PIN_HIGH);
}

void ECUAL_RedSignOFF(void)
{
	Dio_writePin(PIN_2,PIN_LOW);
}