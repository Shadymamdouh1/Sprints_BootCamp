/*
 * Application.c
 *
 * Created: 7/21/2021 7:00:52 PM
 *  Author: Shady mamdouh
 */ 
/****************INCLUDES************************/
#include "types.h"
#include "register.h"
#include "..\MCAL\UART\uart.h"
#include "..\MCAL\UART\uartConfig.h"
#include "..\ECUAL\LED\LED.h"
#include "Application.h"
/************************************************/
/******* Commend buffer*************************/
 static uint8_t Command[6];
 /*********************************************/
 /*********** Commands strings******************/
 static uint8_t Start[]="START";
 static uint8_t Stop[]="STOP";
 static uint8_t Wait[]="WAIT";
 static uint8_t AT[]="AT";
 /************************************************/
 
 /***************response messages*****************/
 static uint8_t welcomeMessage[]="Please Enter a Command\r";
 static uint8_t GreenOnMessage[]="Green LED is ON\r";
 static uint8_t RedOnMessage[]="Red LED is ON\r";
 static uint8_t YellowOnMessage[]="Yellow LED is ON\r";
 static uint8_t OKMessage[]="OK\r";
 static uint8_t InvalidMessage[]="Invalid Command\r";
 /*****************************************************/
 
 /*************Current state**************************/
 uint8_t Current_state ;
 /****************************************************/
 
 
 /************************************************************************
 *                     Private functions
 ***********************************************************************/
 void APP_receiveCommand(void)
 {
	 
	 uint8_t u8_counter=0;
	 uint16_t u16_Data=0;
	 // receive until the terminal sends Enter key
	 while (u16_Data != '\r')
	 {
		 USART_Receive(&u16_Data);
		 Command[u8_counter]=u16_Data;
		 u8_counter++;
	 }
	 if (u16_Data == '\r')
	 {
		 
		 Command[u8_counter]='\0';
	 }
	 
 }
 /***************************************************************************/

 /****************************************************************************/
 enCompareState_t APP_StringsCompare(enStates_t Command_type)
 {
	 uint8_t u8_counter=0;
	 if (Command_type ==START)
	 {
		 while(Command[u8_counter] != '\0' && Start[u8_counter] != '\0' )
		 {
			 if (Command[u8_counter]==Start[u8_counter])
			 {
				 u8_counter++;
				 continue;
			 }
			 else
			 {
				 return NOT_EQUAL;
			 }
		 }
		 return EQUAL;
	 }
	 else if (Command_type==STOP)
	 {
		 while(Command[u8_counter] != '\0' && Stop[u8_counter] != '\0' )
		 {
			 if (Command[u8_counter]==Stop[u8_counter])
			 {
				 u8_counter++;
				 continue;
			 }
			 else
			 {
				 return NOT_EQUAL;
			 }
		 }
		 return EQUAL;
		 
	 }
	 else if (Command_type==WAIT)
	 {
		 while(Command[u8_counter] != '\0' && Wait[u8_counter] != '\0' )
		 {
			 if (Command[u8_counter]==Wait[u8_counter])
			 {
				 u8_counter++;
				 continue;
			 }
			 else
			 {
				 return NOT_EQUAL;
			 }
		 }
		 return EQUAL;
		 
	 }
	 else if (Command_type==AT_OK)
	 {
		 while(Command[u8_counter] != '\0' && AT[u8_counter] != '\0' )
		 {
			 if (Command[u8_counter]==AT[u8_counter])
			 {
				 u8_counter++;
				 continue;
			 }
			 else
			 {
				 return NOT_EQUAL;
			 }
		 }
		 return EQUAL;
		 
	 }
	 return NOT_EQUAL;
 }
 /*************************************************************************/
 
 /**************************************************************************/
 // sends message to the terminal
void APP_sendResponse(uint8_t *ptr)
 {
	 while(*ptr !='\0')
	 {
		 
		 
		 USART_Transmit(*ptr);
		 ptr++;
	 }
 }
 /*************************************************************************/
 
 /******************************************************************************
 *									APIs
 ******************************************************************************/
 
 /*****************************************************/
void APP_init(void)
{
	USART_Init();
	ECUAL_LedInit();
}
/*********************************************************/


/**********************************************************/
void APP_GetState(void)
{    
	//send welcome message to the terminal
	APP_sendResponse(welcomeMessage);
	// receive the command
	APP_receiveCommand();
	//check the command 
	if(APP_StringsCompare(START)==EQUAL)
	{
		Current_state = START ;
	}
	else if (APP_StringsCompare(STOP)==EQUAL)
	{
		Current_state = STOP ;
	}
	else if (APP_StringsCompare(WAIT)==EQUAL)
	{
		Current_state = WAIT ;
	}
	else if (APP_StringsCompare(AT_OK)==EQUAL)
	{
		Current_state = AT_OK ;
	}
	else
	{
		Current_state =InvalidCommand;
	}
	
}
/******************************************************************/

/*****************************************************************/
void APP_UpdateState(void)
{  
	// take action according to current state
	switch(Current_state)
	{
		case START :
		{
			//action 
			ECUAL_GreenSignON();
			ECUAL_YellowSignOFF();
			ECUAL_RedSignOFF();
			APP_sendResponse(GreenOnMessage);
			break;
		}
		case STOP :
		{
			ECUAL_RedSignON();
			ECUAL_YellowSignOFF();
			ECUAL_GreenSignOFF();
			APP_sendResponse(RedOnMessage);
			break;
		}
		case WAIT :
		{
			ECUAL_YellowSignON();
			ECUAL_GreenSignOFF();
			ECUAL_RedSignOFF();
			APP_sendResponse(YellowOnMessage);
			break;
		}
		case AT_OK :
		{
			APP_sendResponse(OKMessage);
			break;
		}
		case InvalidCommand :
		{
			APP_sendResponse(InvalidMessage);
			break;
		}
	}
}

/************************************************************************/
