/*
 * APP.c
 *
 * Created: 7/29/2021 2:12:33 PM
 *  Author: Shady Mamdouh
 */ 

/******************************Includes**************************************/
#include "types.h"
#include "..\MCAL\UART\uart.h"
#include "..\MCAL\UART\uartConfig.h"
#include "..\ECUAL\EEPROM\EEPROM.h"
#include "APP.h"
/**************************************************************************/
/*************************string buffer***********************************/
uint8_t aStringBuffer[255];
/********************Commands*********************************************/
 static uint8_t WriteString[]="WRITE";
 static uint8_t ReadString[]="READ";
/*************************Messages**************************************/
static uint8_t welcomeMessage[]="Please Enter a Command\r";
static uint8_t AddressMessage[]="Please Enter the address\r";
static uint8_t InvaledAddressMessage[]="Invalid address\r";
static uint8_t ReceviedDataMessage[]="Please Enter the Data\r";
static uint8_t DataBaseMessage[]="The Data is: ";
static uint8_t OkMessage[]="OK\r";
static uint8_t WrongCommandMessage[]="Invalid Command\r";
/**********************************************************************/
/**************************Current state******************************/
uint8_t Current_state ;
/**************************Memory Address**************************/
uint8_t u8_Address;
/**************************Data write / read *************************/
uint8_t u8_Data;
/********************************************************************/
void APPInit(void)
{
	/* initialize the UART according to config file */
	USART_Init();
	
	/* initialize EEPROM */
	ECUAL_EEPROMInit();
}

/* get string from terminal using UART */
void APPGetString(void)
{
	/* counter */
	uint8_t u8_counter = 0;
	
	/* start receiving */
	USART_Receive(&aStringBuffer[u8_counter]);
	
	/* check ENTER Key is pressed that is an indicator to the end of string */
	while(aStringBuffer[u8_counter] != '\r')
	{
		u8_counter++;
		USART_Receive(&aStringBuffer[u8_counter]);
	}
	/* ENTER key is pressed in the terminal */
	if (aStringBuffer[u8_counter] == '\r')
	{
		/* close the string by adding null indicator */
		//u8_counter++;
		
		aStringBuffer[u8_counter] = '\0';
	}
	
}

 enCompareState_t APP_StringsCompare(enStates_t Command_type)
 {
	 uint8_t u8_counter=0;
	 if (Command_type ==WRITE)
	 {
		 while(aStringBuffer[u8_counter] != '\0' && WriteString[u8_counter] != '\0' )
		 {
			 if (aStringBuffer[u8_counter]==WriteString[u8_counter])
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
	 else if (Command_type==READ)
	 {
		 while(aStringBuffer[u8_counter] != '\0' && ReadString[u8_counter] != '\0' )
		 {
			 if (aStringBuffer[u8_counter]==ReadString[u8_counter])
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
	
	
 }
 // sends message to the terminal
 void APP_sendResponse(uint8_t *ptr)
 {
	 while(*ptr !='\0')
	 {
		 
		 
		 USART_Transmit(*ptr);
		 ptr++;
	 }
 }
 void APP_GetState(void)
 {
	 //send welcome message to the terminal
	 APP_sendResponse(welcomeMessage);
	 // receive the command
	 APPGetString();
	 
	 //check the command
	 if(APP_StringsCompare(WRITE)==EQUAL)
	 {
		 Current_state = WRITE ;
	 }
	 else if (APP_StringsCompare(READ)==EQUAL)
	 {
		 Current_state = READ ;
	 }
	 
	 else
	 {
		 Current_state =InvalidCommand;
	 }
	 
 }
 uint8_t BinaryStringtoBinary(uint8_t* str)
 {
	 uint8_t u8_counter=0;
	 uint8_t binaryVal=0;
	 uint8_t temp=0;
	 while(str[u8_counter] != '\0')
	 {
		 /* convert from char to int */
		 temp = str[u8_counter] -48;
		 
		if (temp==1)
		{
			binaryVal |=(1<<0); 
		}
		binaryVal = (binaryVal<<1);
		
		 u8_counter++;
		 
	 }
	 binaryVal = (binaryVal>>1);
	 
	 return binaryVal;
 }
 
 
 void APP_UpdateState(void)
 {
	 
	 // take action according to current state
	 switch(Current_state)
	 {
		 case WRITE :
		 {   
			 APP_sendResponse(AddressMessage);
			 APPGetString();
			 u8_Address=BinaryStringtoBinary(aStringBuffer);
			 if (u8_Address > 255)
			 {
				 APP_sendResponse(InvaledAddressMessage);
				 break;
			 }
			 APP_sendResponse(OkMessage);
			 APP_sendResponse(ReceviedDataMessage);
			 APPGetString();
			 u8_Data = aStringBuffer[0];
			 
			 ECUAL_EEPROMWrite(0,u8_Address,u8_Data);
			 break;
		 }
		 case READ :
		 {
			 APP_sendResponse(AddressMessage);
			 APPGetString();
			 u8_Address=BinaryStringtoBinary(aStringBuffer);
			 if (u8_Address > 255)
			 {
				 APP_sendResponse(InvaledAddressMessage);
				 break;
			 }
			 APP_sendResponse(DataBaseMessage);
			 ECUAL_EEPROMRead(0,u8_Address,&u8_Data);
			 USART_Transmit(u8_Data);
			 USART_Transmit('\r');
			 break;
		 }
		 case InvalidCommand :
		 {
			  APP_sendResponse(WrongCommandMessage);
			  break;
		 }
	 }
	 
	 
 }