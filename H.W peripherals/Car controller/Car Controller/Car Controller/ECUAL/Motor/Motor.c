/*
 * Motor.c
 *
 * Created: 7/16/2021 5:52:26 PM
 *  Author: Shady mamdouh 
 */ 
#include "types.h"
#include "..\..\MCAL\DIO\Dio.h"
#include "Motor.h"
#include "..\..\MCAL\SW_PWM\SW_PWM.h"
#include "..\..\MCAL\Timer\timer.h"
#include "..\..\MCAL\SW_PWM\PWM_Cfg.h"
enuMotor_Status_t Motor_init(void)
{    
	//
	SWPwm_Init();
	// for first motor PORTA pins 1&2
	arMotorsData[0].MotorID=0;
	arMotorsData[0].PositvePinConfg.u8_PortNum=PORT_A;
	arMotorsData[0].PositvePinConfg.u8_PinNum=1;
	arMotorsData[0].PositvePinConfg.u8_Direction=DIO_PIN_DIR_OUTPUT;
	arMotorsData[0].PositvePinConfg.u8_InitState=0;
	arMotorsData[0].NegativePinConfg.u8_PortNum=PORT_A;
	arMotorsData[0].NegativePinConfg.u8_PinNum=2;
	arMotorsData[0].NegativePinConfg.u8_Direction=DIO_PIN_DIR_OUTPUT;
	arMotorsData[0].NegativePinConfg.u8_InitState=0;
	Dio_init(&arMotorsData[0].PositvePinConfg);
	Dio_init(&arMotorsData[0].NegativePinConfg);
	// for second motor PORTA pins 4&5 
	arMotorsData[1].MotorID=1;
	arMotorsData[1].PositvePinConfg.u8_PortNum=PORT_A;
	arMotorsData[1].PositvePinConfg.u8_PinNum=4;
	arMotorsData[1].PositvePinConfg.u8_Direction=DIO_PIN_DIR_OUTPUT;
	arMotorsData[1].PositvePinConfg.u8_InitState=0;
	arMotorsData[1].NegativePinConfg.u8_PortNum=PORT_A;
	arMotorsData[1].NegativePinConfg.u8_PinNum=5;
	arMotorsData[1].NegativePinConfg.u8_Direction=DIO_PIN_DIR_OUTPUT;
	arMotorsData[1].NegativePinConfg.u8_InitState=0;
	Dio_init(&arMotorsData[1].PositvePinConfg);
	Dio_init(&arMotorsData[1].NegativePinConfg);
}
enuMotor_Status_t Motor_moveForward(uint8_t u8_motorID, uint8_t u8_speed)
{
	//Clear pins 
	Dio_writePin(arMotorsData[u8_motorID].PositvePinConfg.u8_PinNum , PIN_LOW);
	Dio_writePin(arMotorsData[u8_motorID].NegativePinConfg.u8_PinNum , PIN_LOW);
	// to move forward positive pin will be High and the negative one will be Low
	Dio_writePin(arMotorsData[u8_motorID].PositvePinConfg.u8_PinNum , PIN_HIGH);
	Dio_writePin(arMotorsData[u8_motorID].NegativePinConfg.u8_PinNum , PIN_LOW);
	//Enable PWM
	SWPwm_Start(SW_PWMChannels[0],5, u8_speed);
}

enuMotor_Status_t Motor_moveBackward(uint8_t u8_motorID, uint8_t u8_speed)
{
	//Clear pins
	Dio_writePin(arMotorsData[u8_motorID].PositvePinConfg.u8_PinNum , PIN_LOW);
	Dio_writePin(arMotorsData[u8_motorID].NegativePinConfg.u8_PinNum , PIN_LOW);
	// to move back forward positive pin will be Low and the negative one will be High
	Dio_writePin(arMotorsData[u8_motorID].PositvePinConfg.u8_PinNum ,PIN_LOW );
	Dio_writePin(arMotorsData[u8_motorID].NegativePinConfg.u8_PinNum ,PIN_HIGH );
	
	//Enable PWM 
	SWPwm_Start(SW_PWMChannels[0],5, u8_speed);
}
enuMotor_Status_t Motor_stop(uint8_t u8_motorID)
{
	//Clear pins
	Dio_writePin(arMotorsData[u8_motorID].PositvePinConfg.u8_PinNum , PIN_LOW);
	Dio_writePin(arMotorsData[u8_motorID].NegativePinConfg.u8_PinNum , PIN_LOW);
	//Disable PWM 
	SWPwm_Stop(SW_PWMChannels[0]);
}