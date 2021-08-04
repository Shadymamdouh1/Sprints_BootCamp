/*
 * motor.c
 *
 * Created: 8/3/2021 8:04:06 PM
 *  Author: Shady Mamdouh 
 */ 
/**********INCLUDES**********************/
#include "types.h"
#include "..\..\MCAL\DIO\DIO.h"
#include "motor.h"

/****************************************/

void MotorInit()
{
	/* initialize Motor PIN */
	strDio_pins.u8_PortNum=MOTOR_PORT;
	strDio_pins.u8_PinNum=MOTOR_PIN;
	strDio_pins.u8_Direction=DIO_PIN_DIR_OUTPUT;
	Dio_init(&strDio_pins);
	
}
void MotorON(void)
{
	Dio_writePin(MOTOR_PORT,MOTOR_PIN,PIN_HIGH);
}
void MotorOFF(void)
{
	Dio_writePin(MOTOR_PORT,MOTOR_PIN,PIN_LOW);
}