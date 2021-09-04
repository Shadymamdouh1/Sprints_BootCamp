/*****************************************************************************
* Module: Button Module
* File Name: Button.h
* Description: Header file for Button Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/ 

#ifndef BUTTON_H_
#define BUTTON_H_

/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- INCLUDES *-*-*-*-*-*/
#include "Button_Cfg.h"
#include "../../../MCAL/Dio Module/Dio.h"
#include "../../../Microcontroller/Std_Types.h"
#include "../../../Libraries/Common_Macros.h"

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

/*- STRUCTS AND UNIONS -------------------------------------*/
typedef struct
{
	uint8_t u8_Button_DioId;
	uint8_t u8_pullUpOrDown;
}strButton_Config_t;

/*******************************************************************************
 *                      Function Prototypes                                    *
 *******************************************************************************/
/* Function to initialize the button module */
enuBttn_Status_t Button_init(void);

/* Function to get the logic state of the button */
enuBttn_Status_t Button_getState(uint8_t u8_bttnID, uint8_t* pu8_state);

/* configuration variable */
extern strButton_Config_t strButton_Config[BUTTONS_USED];
#endif /* BUTTON_H_ */