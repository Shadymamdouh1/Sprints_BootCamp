/*
 * Motors.c
 *
 * Created: 8/7/2021 6:19:00 AM
 *  Author: Shady Madouh
 */ 
#include "types.h"
#include "..\..\MCAL\DIO\DIO.h"
#include "Motors.h"
#include "..\..\MCAL\TIMER\timer.h"
#include "..\..\MCAL\TIMER\timer_Cfg.h"

void Motor_Delay_ms(uint32_t u32_Timemsec)
{
	uint32_t u32_counter =0;
	for (u32_counter=0;u32_counter<u32_Timemsec;u32_counter++)
	{
		/* this function takes timer id and number of ticks so if fck 1mega */
		/* the timer time base will be  1micro so we pass 1000 micro to represent 1 msec*/
		GptStart_Sync(0,1000);
	}
}
MOTOR_Init(void)
{
	/* timer init */
	GptInit();
	strDio_pins.u8_PortNum =M1PORT;
	strDio_pins.u8_PinNum =M1PIN1;
	strDio_pins.u8_Direction= DIO_PIN_DIR_OUTPUT;
	strDio_pins.u8_InitState=PIN_LOW;
	Dio_init(&strDio_pins);
	
	strDio_pins.u8_PortNum =M1PORT;
	strDio_pins.u8_PinNum =M1PIN2;
	strDio_pins.u8_Direction= DIO_PIN_DIR_OUTPUT;
	strDio_pins.u8_InitState=PIN_LOW;
	Dio_init(&strDio_pins);
	
	strDio_pins.u8_PortNum =M2PORT;
	strDio_pins.u8_PinNum =M2PIN;
	strDio_pins.u8_Direction= DIO_PIN_DIR_OUTPUT;
	strDio_pins.u8_InitState=PIN_LOW;
	Dio_init(&strDio_pins);
}

void CardMotorRight(void)
{
	Dio_writePin(M1PORT,M1PIN1,PIN_HIGH);
	Dio_writePin(M1PORT,M1PIN2,PIN_LOW);
	Motor_Delay_ms(2000);
	Dio_writePin(M1PORT,M1PIN1,PIN_LOW);
	Dio_writePin(M1PORT,M1PIN2,PIN_LOW);
}
void CardMotorLeft(void)
{
	Dio_writePin(M1PORT,M1PIN1,PIN_LOW);
	Dio_writePin(M1PORT,M1PIN2,PIN_HIGH);
	Motor_Delay_ms(2000);
	Dio_writePin(M1PORT,M1PIN1,PIN_LOW);
	Dio_writePin(M1PORT,M1PIN2,PIN_LOW);
}
void MoneyMotorON(void)
{
	Dio_writePin(M2PORT,M2PIN,PIN_HIGH);
	Motor_Delay_ms(2000);
	Dio_writePin(M2PORT,M2PIN,PIN_LOW);
}