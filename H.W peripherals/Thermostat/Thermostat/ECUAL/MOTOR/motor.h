/*
 * motor.h
 *
 * Created: 8/3/2021 8:04:20 PM
 *  Author: Shady Mamdouh 
 */ 


#ifndef MOTOR_H_
#define MOTOR_H_

/************motor pin *******************/
#define MOTOR_PORT PORT_C
#define MOTOR_PIN PIN_3
/****************************************/

/**************APIs********************/
void MotorInit();
void MotorON(void);
void MotorOFF(void);
/*****************************************/
#endif /* MOTOR_H_ */