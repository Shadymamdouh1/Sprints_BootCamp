/*
 * Application.h
 *
 * Created: 7/21/2021 7:01:16 PM
 *  Author: Shady mamdouh
 */ 


#ifndef APPLICATION_H_
#define APPLICATION_H_
#include "types.h"

/************************************************************/
/****************** States********************************/
typedef enum enStates_t
{
	START,
	STOP,
	WAIT,
	AT_OK,
	InvalidCommand
	
}enStates_t;
/*******************************************************/
/************Compare return***************************/
typedef enum enCompareState_t
{
	EQUAL,
	NOT_EQUAL
	
}enCompareState_t;
/**************************************************/

/**********************************************************
*						APIs
*********************************************************/
/******************************************************************************
* Name : APP_init
* Description : initialize the APP module and the the lower layer modules
*/
void APP_init(void);
/******************************************************************************
* Name : APP_GetState
* Description : used to receive command from the terminal and assign 
*               the current state
*/
void APP_GetState(void);
/******************************************************************************
** Name : APP_UpdateState
* Description : used to check the current state and take the related action and 
*				response message
*
*/
void APP_UpdateState(void);

#endif /* APPLICATION_H_ */