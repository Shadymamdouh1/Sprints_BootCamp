/*
 * Motor.h
 *
 * Created: 7/15/2021 11:13:02 PM
 *  Author: Ahmed Nabil
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Motor_LCfg.h"
#include "../../MCAL/Dio Module/Dio.h"
#include "../../MCAL/SWPwm Module/SWPwm.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define MOTOR_DIR_CLK_WISE				0U
#define MOTOR_DIR_ANTI_CLK_WISE			1U

#define MOTOR_STOPPED				0U
#define MOTOR_RUNNING				1U
/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/

/*
 * Data Type for Motor state
 */
typedef uint8_t MotorState_t;

/*
 * Data Type for Motor Channel ID
 */
typedef uint8_t MotorChannel_t;

/*
 * Data Type for Motor Speed
 */
typedef uint8_t MotorSpeed_t;

/*
 * Data Type for Motor Direction
 */
typedef uint8_t MotorDir_t;

/*
 * Data Type for Motor return status
 */
typedef enum
{
	MOTOR_STATUS_ERROR_NOK,
	MOTOR_STATUS_ERROR_OK,
	MOTOR_STATUS_ERROR_ID_INVALID,
	MOTOR_STATUS_ERROR_SPD_INVALID,
	MOTOR_STATUS_ERROR_DIR_INVALID,
	MOTOR_STATUS_ERROR_RUNNING,
	MOTOR_STATUS_INIT,
	MOTOR_STATUS_UNINIT
}Motor_Status_t;

/*
 * Data Type for Motor configurations
 */
typedef struct  
{
	uint8_t u8_MotorPwmChannel;
	uint8_t u8_MotorDirPin1;
	uint8_t u8_MotorDirPin2;
	uint16_t u16_Frequency;
}Motor_Config_t;
/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the motor module */
Motor_Status_t Motor_init(void);

/* Function to move the motor forward with given speed in % */
Motor_Status_t Motor_run(MotorChannel_t u8_motorID, MotorSpeed_t u8_speed, MotorDir_t u8_direction);

/* Function to move the motor backward with given speed in % */
//enuMotor_Status_t Motor_moveBackward(uint8_t u8_motorID, uint8_t u8_speed);

/* Function to stop motor */
Motor_Status_t Motor_stop(MotorChannel_t u8_motorID);

/*******************************************************************************
 *                       External Variables                                    *
 *******************************************************************************/
extern const Motor_Config_t MotorsConfigurations_str[MOTORS_USED_NUM];

#endif /* MOTOR_H_ */