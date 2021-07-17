/*
 * Button.h
 *
 * Created: 7/15/2021 6:36:15 PM
 *  Author: Shady Mamdouh 
 */ 


#ifndef BUTTON_H_
#define BUTTON_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
//#include "Button_Cfg.h"
#include "types.h"
#include "..\..\MCAL\DIO\Dio.h"
/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/
#define BUTTON_STATE_PRESSED		0U
#define BUTTON_STATE_RELEASED		1U
/***********************************BUTTONS NAMES*************************************/
#define GearButton		0
#define MoveButton		1
#define RightButton		2
#define LeftButton		3
//#define BackButton		4
/*******************************************************************************
 *                          Module Data Types                                  *
 *******************************************************************************/
/*
 * Data Type for Button return status
 */
typedef enum
{
	BTTN_STATUS_ERROR_NOK,
	BTTN_STATUS_ERROR_OK,
	BTTN_STATUS_ERROR_INVALID
}enuBttn_Status_t;

/*
 * Data Type for GPT state
 */

//*****************************Button  data***********************************************/
typedef struct strButtonData_t
{
uint8_t ButtonID ;
strDio_Config_t PIN_config;
uint8_t Button_State;	
}strButtonData_t;
/************************array of buttons data****************************************/
strButtonData_t arButtonData[4];

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the button module */
enuBttn_Status_t Button_init(void);

/* Function to get the state of the button */
enuBttn_Status_t Button_getState(uint8_t u8_bttnID, uint8_t * pu8_state);

/* Function to update the state of the button */
enuBttn_Status_t Button_updateState(uint8_t u8_bttnID);

#endif /* BUTTON_H_ */