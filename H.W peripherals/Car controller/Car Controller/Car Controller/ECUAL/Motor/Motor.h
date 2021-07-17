/*
 * Motor.h
 *
 * Created: 7/16/2021 5:52:48 PM
 *  Author: Shady mamdouh 
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "..\..\MCAL\DIO\Dio.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define RightMotorID 0
#define LeftMotorID  1
/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
 * Data Type for Motor return status
 */
typedef enum
{
	MOTOR_STATUS_ERROR_NOK,
	MOTOR_STATUS_ERROR_OK,
	MOTOR_STATUS_ERROR_INVALID
}enuMotor_Status_t;
//***************************Motor Data***************************************/
typedef struct strMotorData
{   uint8_t MotorID;
	strDio_Config_t PositvePinConfg ;
	strDio_Config_t NegativePinConfg ;
	
}strMotorData;
// array of motors
strMotorData arMotorsData[2];
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the motor module */
enuMotor_Status_t Motor_init(void);

/* Function to move the motor forward with given speed in % */
enuMotor_Status_t Motor_moveForward(uint8_t u8_motorID, uint8_t u8_speed);

/* Function to move the motor backward with given speed in % */
enuMotor_Status_t Motor_moveBackward(uint8_t u8_motorID, uint8_t u8_speed);

/* Function to stop motor */
enuMotor_Status_t Motor_stop(uint8_t u8_motorID);




#endif /* MOTOR_H_ */