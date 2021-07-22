/*
 * LED.h
 *
 * Created: 7/21/2021 6:32:40 PM
 *  Author: Shady Mamdouh
 */ 


#ifndef LED_H_
#define LED_H_
/***************APIs***********************************
* Name: ECUAL_LedInit
* Description : initialize LED module and the Dio module 
*/
void ECUAL_LedInit(void);
/*****************************************************
* Name: ECUAL_GreenSignON
* Description : Enables Green Led
*/
void ECUAL_GreenSignON(void);
/****************************************************
* Name: ECUAL_GreenSignOFF
* Description : Disable Green Led
*/
void ECUAL_GreenSignOFF(void);
/****************************************************
* Name: ECUAL_YellowSignON
* Description : Enables Yellow Led
*/
void ECUAL_YellowSignON(void);
/****************************************************
* Name: ECUAL_YellowSignOFF
* Description : Disable Yellow Led
*/
void ECUAL_YellowSignOFF(void);
/****************************************************
* Name: ECUAL_RedSignON
* Description :Enable Red Led
*/
void ECUAL_RedSignON(void);
/****************************************************
* Name: ECUAL_RedSignOFF
* Description :Disable Red Led
*/
void ECUAL_RedSignOFF(void);
/***************************************************/
#endif /* LED_H_ */