/*****************************************************************************
* Module: Button Module
* File Name: buttonDebounceHandler.h
* Description: Header file for Button Debounce Handler Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/ 


#ifndef BUTTONDEBOUNCEHANDLER_H_
#define BUTTONDEBOUNCEHANDLER_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "../Button Driver/Button.h"
#include "../../../MCAL/Gpt Module/Gpt.h"
#include "buttonDebounceHandler_Cfg.h"
#include "../../../MCAL/Dio Module/Dio.h"
#include "../../../Microcontroller/Std_Types.h"
#include "../../../Microcontroller/Delay Module/Delay.h"
#include "../../../Libraries/Common_Macros.h"

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
/* Button State  */
#define BUTTON_STATE_RELEASED		(9U)
#define BUTTON_STATE_PRESSED		(10U)

/*- Primitive Types
-------------------------------*/
typedef void(*callBackFun_t)(void);
/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t  u8_buttonId;
	uint8_t	 u8_timerId;
	uint16_t u16_delayTicks;
	uint8_t	 u8_delayType;	 
	uint8_t	 u8_buttonCheck_PollingOrExtInt;
}strButtonDebounce_Config_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
Std_ReturnType debounceHandler_updateButtonState(uint8_t debouncingButtonId);

Std_ReturnType debounceHandler_getButtonState(uint8_t debouncingButtonId, uint8_t* debouncingButtonState);



/* Event Trigger Call Back Functions for External Int */
void eventReceived_Button1_CallBack(void);
void eventReceived_Button2_CallBack(void);

/* Timers Call Back Functions */
void callBack_Button_1(void);
void callBack_Button_2(void);

/* configuration variable */
strButtonDebounce_Config_t strButtonDeounce_Config[DEBOUNCE_BUTTONS_USED];

#endif /* BUTTONDEBOUNCEHANDLER_H_ */