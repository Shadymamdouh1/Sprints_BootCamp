/*
 * APP.h
 *
 * Created: 7/30/2021 1:02:32 PM
 *  Author: Shady Mamdouh
 */ 


#ifndef APP_H_
#define APP_H_

/******************************************************************************
							    ENUMS
******************************************************************************/
typedef enum CardState_t
{
	PROGRAMMED,
	NOT_PROGRAMMED
}CardState_t;
/***************************************************************************/
typedef enum ModeState_t
{
	USER_MODE,
	ENTRY_MODE,
	ADMIN_MODE
	}ModeState_t;
typedef enum enCompareCommand_t
{
	EQUAL,
	NOT_EQUAL
}enCompareCommand_t;
/****************************************************************************/
typedef enum enDatatoStore_t
{
	CARD_HOLDER_NAME,
	PA_NUM,    // primary account Number
	PIN        // Password
	}enDatatoStore_t;

/******************************************************************************/
typedef enum enComandCompare_t
{
	ADMIN,
	USER
	}enComandCompare_t;

/**************************************************************************************************
									      APIs
**************************************************************************************************/
void APP_AppInit(void);
void APP_UpdateState(void);

/*************************************************************************************************/
#endif /* APP_H_ */