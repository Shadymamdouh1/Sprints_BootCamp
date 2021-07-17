/*
 * Button.c
 *
 * Created: 7/16/2021 1:39:48 PM
 *  Author: Shady mamdouh 
 */ 
/***************INCLUDES**************/
#include "types.h"
#include "..\..\MCAL\DIO\Dio.h"
#include "Button.h"
#include "register.h"
/***********************************/
/************ array of pointers to holds buttons status******************/
uint8_t Buttons_status[5];
enuBttn_Status_t Button_init(void)
{   
	
	/********************************************************/
	
	
	/********************************************************/
	//PB0 input FOR Gear//
	arButtonData[0].Button_State=BUTTON_STATE_RELEASED;
	arButtonData[0].ButtonID=0;
	arButtonData[0].PIN_config.u8_PortNum=PORT_B;
	arButtonData[0].PIN_config.u8_Direction=DIO_PIN_DIR_INPUT;
	arButtonData[0].PIN_config.u8_PinNum=8; //portb pin 0
	arButtonData[0].PIN_config.u8_InitState=1; // pull up
	Dio_init(&arButtonData[0].PIN_config);
	//PB1 input FOR Move forward//
	arButtonData[1].Button_State=BUTTON_STATE_RELEASED;
	arButtonData[1].ButtonID=1;
	arButtonData[1].PIN_config.u8_PortNum=PORT_B;
	arButtonData[1].PIN_config.u8_Direction=DIO_PIN_DIR_INPUT;
	arButtonData[1].PIN_config.u8_PinNum=9; //portb pin 0
	arButtonData[1].PIN_config.u8_InitState=1; // pull up
	Dio_init(&arButtonData[1].PIN_config);
	
	//PB2 input FOR Move right//
	arButtonData[2].Button_State=BUTTON_STATE_RELEASED;
	arButtonData[2].ButtonID=2;
	arButtonData[2].PIN_config.u8_PortNum=PORT_B;
	arButtonData[2].PIN_config.u8_Direction=DIO_PIN_DIR_INPUT;
	arButtonData[2].PIN_config.u8_PinNum=10; //portb pin 0
	arButtonData[2].PIN_config.u8_InitState=1; // pull up
	Dio_init(&arButtonData[2].PIN_config);
	//PB3 input FOR Move left//
	arButtonData[3].Button_State=BUTTON_STATE_RELEASED;
	arButtonData[3].ButtonID=3;
	arButtonData[3].PIN_config.u8_PortNum=PORT_B;
	arButtonData[3].PIN_config.u8_Direction=DIO_PIN_DIR_INPUT;
	arButtonData[3].PIN_config.u8_PinNum=11; //portb pin 0
	arButtonData[3].PIN_config.u8_InitState=1; // pull up
	Dio_init(&arButtonData[3].PIN_config);
	
}


enuBttn_Status_t Button_getState(uint8_t u8_bttnID, uint8_t * pu8_state)
{
	* pu8_state =arButtonData[u8_bttnID].Button_State;
}

enuBttn_Status_t Button_updateState(uint8_t u8_bttnID)
{
	Dio_readPin(arButtonData[u8_bttnID].PIN_config.u8_PinNum,&arButtonData[u8_bttnID].Button_State);
}