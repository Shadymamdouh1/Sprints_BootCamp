/*
 * Motors.h
 *
 * Created: 8/7/2021 6:19:30 AM
 *  Author: Shady Mamdouh
 */ 


#ifndef MOTORS_H_
#define MOTORS_H_

#define M1PORT PORT_C
#define M2PORT PORT_C
 /* M1 has two directions movement */
 #define M1PIN1 PIN_6
 #define M1PIN2 PIN_7
 /* M2 has one direction */
  #define M2PIN PIN_5

void MOTOR_Init(void);
void CardMotorRight(void);
void CardMotorLeft(void);
void MoneyMotorON(void);
void Motor_Delay_ms(uint32_t u32_Timemsec);

#endif /* MOTORS_H_ */