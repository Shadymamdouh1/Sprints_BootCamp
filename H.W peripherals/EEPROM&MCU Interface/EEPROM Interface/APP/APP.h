/*
 * APP.h
 *
 * Created: 7/29/2021 2:12:48 PM
 *  Author: Shady Mamdouh
 */ 


#ifndef APP_H_
#define APP_H_
/****************** States********************************/
typedef enum enStates_t
{
	WRITE,
	READ,
	InvalidCommand
	
}enStates_t;
/*******************************************************/
/************Compare return***************************/
typedef enum enCompareState_t
{
	EQUAL,
	NOT_EQUAL
	
}enCompareState_t;

/************************************************************************
						APIs
**************************************************************************/
void APPInit(void);
void APP_GetState(void);
void APP_UpdateState(void);
/************************************************************************/
#endif /* APP_H_ */