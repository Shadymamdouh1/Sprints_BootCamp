/*
 * APP.c
 *
 * Created: 7/30/2021 1:02:21 PM
 *  Author: Shady Mamdouh
 */ 
/***************************************************************************
								INCLUDES
***************************************************************************/
#include "types.h"
#include "..\ECUAL\EEPROM\EEPROM.h"
#include "..\MCAL\UART\uart.h"
#include "..\MCAL\UART\uartConfig.h"
#include "..\MCAL\SPI\spi.h"
#include "..\MCAL\SPI\spiConfig.h"
#include "APP.h"
#include "..\MCAL\SPI\register.h"
/*************************************************************************/
/*************************string buffers***********************************/
  /* for Receiving Command From Terminal Over UART */
uint8_t aStringBuffer[255];
/* Current Data in user Mode to be sent to th ATM*/
#define DATA_BUFFER_SIZE 28UL
uint8_t aDataBuffer[DATA_BUFFER_SIZE];

/********************Commands*********************************************/
static uint8_t AdminString[]="ADMIN";
static uint8_t UserString[]="USER";
/*************************Messages****************************************/
//static uint8_t welcomeMessage[]="Please Enter a Command\r";
static uint8_t WrongCommandMessage[]="Invalid Command\r";
static uint8_t NotProgrammedMessage[]=" The Card is not Programmed please Enter the Admin Mode\r";
static uint8_t UserModeMessage[]="The Card is initialized before\r please Enter ADMIN command for edit or USER for continue\r";
static uint8_t HolderNameMessage[]="Please Enter the Card Holder Name\r";
static uint8_t HolderNameExceedMax[]="Holder Name must be Smaller than or equal 9 characters\r";
static uint8_t PrimaryACCNUMMessage[]="Please Enter the Primary Account Number\r";
static uint8_t PANNumExceedMax[]= "PAN must be equal 9 characters\r";
static uint8_t PINMessage[]="Please Enter the PIN\r";
static uint8_t PINNumExceedMax[]="PIN must equal 4 Numbers\r";
/***********************************************************************************************/
    /* this number will be stored in EEPROM at Page 0 Loc 0 if the Card is previously Programmed */
#define FIRST_LOC_Data 55UL
/***********************************************************************************************/
uint8_t gu8_SPIcounter=0;
uint8_t flusher;
/*************************************************************************************************/
     /* start addresses for different data will be stored in the EEPROM */
#define CARD_PROGRAMMED_CHECK_ADD    0UL	 
#define CARD_HOLDER_NAME_ADD		 1UL
#define PAN_ADD						 11UL
#define PIN_ADD						 21ul	
/**********************************************************************************************/
 #define MAX_NAME_SIZE 10UL
 #define MAX_PAN_SIZE  10UL
 #define MAX_PIN_SIZE  5UL
 #define EEROR 0UL
 #define NO_ERROR 1UL
 #define EEPROM_PAGE_0   0UL
 /***********************************************************************************************/
                      /* Current Mode State  user or admin */
int CurrentModeState = ENTRY_MODE; 
/*************************************************************************************************
							        Private Functions 
************************************************************************************************/
  /* Send Message to the terminal */
static void APP_APPToTerminalResponse(uint8_t *pString)
{
	while(*pString !='\0')
	{
		USART_Transmit(*pString);
		pString++;
	}
}
/*************************************************************************************************/
/* Receive Message From the terminal */
static uint8_t APP_ReceiveFromTerminal(void)
{
	/* counter */
	uint8_t u8_counter = 0;
	/* string size */
	uint8_t u8_STRSize=0;
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
		
		aStringBuffer[u8_counter] = '\0';
	}
	u8_STRSize =(u8_counter+1);
	/* return string size */
	return u8_STRSize ;
}
/******************************************************************************************/
CardState_t APP_CheckCardState(void)
{
	uint8_t u8_Data;
	
	
	ECUAL_EEPROMRead(CARD_PROGRAMMED_CHECK_ADD,&u8_Data);
	
	/*Check if The Card is Previously Programmed */ 
	if (u8_Data==FIRST_LOC_Data)
	{
		return PROGRAMMED;
	}
	else
	{
		return NOT_PROGRAMMED;
	}
}
/*******************************************************************************************/
enCompareCommand_t APP_CommandCompare(enComandCompare_t CommandType)
{
	uint8_t u8_counter=0;
	if (CommandType==ADMIN)
	{
		while(aStringBuffer[u8_counter] != '\0' && AdminString[u8_counter] != '\0' )
		{
			if (aStringBuffer[u8_counter]==AdminString[u8_counter])
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
	else if (CommandType==USER)
	{
		while(aStringBuffer[u8_counter] != '\0' && AdminString[u8_counter] != '\0' )
		{
			if (aStringBuffer[u8_counter]==UserString[u8_counter])
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
/********************************************************************************************/
/* this function will be used to convert PIN String to Numeric string */
void APP_ConvertStringToNumericString(uint8_t *pString)
{
	/* counter */
	uint8_t u8_counter=0;
	while(pString[u8_counter] != '\0')
	{
		/* 48 is the difference between the number as a Character and as a Numeric value */
		pString[u8_counter] =pString[u8_counter] - 48 ;   
		u8_counter ++;
	}
}
/********************************************************************************************/
void APP_SmallDelay(void)
{
	volatile uint32_t u32_counter;
	for (u32_counter=0;u32_counter<500;u32_counter++);

}
/********************************************************************************************/
uint8_t APP_StoreDataEEPROM(uint8_t *String,enDatatoStore_t DataType)
{  
	APP_SmallDelay();
	/* counter */
	uint8_t u8_counter=0;
	/* max size */
	uint8_t u8_MaxSize =0;
	/* start location */
	uint16_t u16_AdressLoc; 
	
	if (DataType==CARD_HOLDER_NAME)
	{
		/* will start from address 1 */
		u16_AdressLoc = CARD_HOLDER_NAME_ADD ;
		u8_MaxSize = MAX_NAME_SIZE	;
	}
	else if (DataType==PA_NUM)
	{
		/* will start from address 11 */
		u16_AdressLoc = PAN_ADD;
		u8_MaxSize =MAX_PAN_SIZE;
	}
	else if (DataType==PIN)
	{
		/* will start from address 21 */
		u16_AdressLoc = PIN_ADD;
		u8_MaxSize =MAX_PIN_SIZE;
	}
	else
	{
		return EEROR;
	}
	while(String[u8_counter] != '\0' && u8_counter != u8_MaxSize )
	{
		ECUAL_EEPROMWrite(u16_AdressLoc,String[u8_counter]);
		u8_counter++;
		u16_AdressLoc++;
		APP_SmallDelay();
		

	}
	if (String[u8_counter] == '\0' && u8_counter != u8_MaxSize )
	{ 
		/* add Null indicator in case of CARD_HOLDER_NAME or PA_NUM */
		if (DataType==CARD_HOLDER_NAME || DataType == PA_NUM)
		{
			ECUAL_EEPROMWrite(u16_AdressLoc,String[u8_counter]);
			return NO_ERROR;
		}
		
	}
	return NO_ERROR;
}
/********************************************************************************************/
  /* will Copy the Data from EEPROM to aDataBuffer */ 
void APP_ReadAllData(void)
{
	
	APP_SmallDelay();
	/* first Data address location */
	uint16_t u16_location = CARD_PROGRAMMED_CHECK_ADD;
	
	uint8_t u8_Counter =1;
	/* Read Data sequentially and Store it in the Data Buffer */  
	for(u8_Counter=1;u8_Counter<DATA_BUFFER_SIZE-1;u8_Counter++)
	{
		
		
		
		ECUAL_EEPROMRead(u16_location,(&aDataBuffer[u8_Counter]));
		u16_location++;
		APP_SmallDelay();
	}
	
}
/**********************************************************************************************/
void APP_TransDataOverSPI(void)
{
	uint8_t u8_counter ;
	for(u8_counter=0;u8_counter<DATA_BUFFER_SIZE;u8_counter++)
	{
		MCAL_SPISlaveTrans(aDataBuffer[u8_counter]);
	}
}
/**************************************************************************************************
									      APIs
**************************************************************************************************/
void APP_AppInit(void)
{
	ECUAL_EEPROMInit();
	USART_Init();
	MCAL_SpiInit();
	
	uint8_t u8_CARD_MODE;
	
	u8_CARD_MODE =APP_CheckCardState();
	if (u8_CARD_MODE == PROGRAMMED)
	{
	/* Copy data from EEPROM TO Data buffer */
	APP_ReadAllData();
	/* Display the User Mode Message */
	APP_APPToTerminalResponse(UserModeMessage);
	while(1)
	{
		/* Receive Command */
		APP_ReceiveFromTerminal();
		
		/* Compare with ADMIN Command */
		if (APP_CommandCompare(ADMIN)==EQUAL)
		{
			CurrentModeState = ADMIN_MODE;
			break;
		}
		else if(APP_CommandCompare(USER)==EQUAL)
		{
			CurrentModeState = USER_MODE;
			break;
		}
		else
		{
			/* Display the Wrong Command Message */
			APP_APPToTerminalResponse(WrongCommandMessage);
		}
	}
	
	
	}
	else{
		CurrentModeState = ENTRY_MODE;
		
	}
	
	
	
}
/************************************************************************************************/
/***************************************************************************************************/
void APP_UpdateState(void)
{
	uint8_t u8_counter=0 ;
	uint8_t u8_flag =0;
	uint8_t u8_MaxSize;
	switch(CurrentModeState)
	{
		case USER_MODE :
		{
			
			APP_TransDataOverSPI();
			
			
			
			
			break;
		}
		case ENTRY_MODE :
		{
			while(1)
			{
				/* Display Not Programmed Message Message */
				APP_APPToTerminalResponse(NotProgrammedMessage);
				/* Receive Command */
				APP_ReceiveFromTerminal();
				
				/* Compare with ADMIN Command */
				if (APP_CommandCompare(ADMIN)==EQUAL)
				{
					CurrentModeState = ADMIN_MODE;
					break;
				}
				else
				{
					/* Display the Wrong Command Message */
					APP_APPToTerminalResponse(WrongCommandMessage);
				}
				
			}
			break;
			
		}
		case ADMIN_MODE :
		{   
			
			
			
			while(1)
			{
				/* Display Holder Name Message */
				APP_APPToTerminalResponse(HolderNameMessage);
				
				u8_MaxSize =APP_ReceiveFromTerminal();
				if (u8_MaxSize > MAX_NAME_SIZE)
				{
					APP_APPToTerminalResponse(HolderNameExceedMax);
					
				}
				else 
				{ 
					 u8_counter=0 ;
					 u8_flag =0;
					for (u8_counter=0;u8_counter<u8_MaxSize-1;u8_counter++)
					{
						/* check if the name contains any numbers */
						if (aStringBuffer[u8_counter]>47 && aStringBuffer[u8_counter] < 58  )
						{
							APP_APPToTerminalResponse("The name must not contains any numbers\r");
							u8_flag =1;
							break; // from for
						}
					}
					if (u8_flag==1)
					{
						continue;
					}
					else
					{
						APP_StoreDataEEPROM(aStringBuffer,CARD_HOLDER_NAME);
						break;
					}
					
			    }
			
			}
			while(1)
			{
				/* Display PAN Message */
				APP_APPToTerminalResponse(PrimaryACCNUMMessage);
				
				/* get Entered Data and check length */
				/* should be 9 characters */
				u8_MaxSize =APP_ReceiveFromTerminal();
				if (u8_MaxSize > MAX_PAN_SIZE || u8_MaxSize < MAX_PAN_SIZE )
				{
					APP_APPToTerminalResponse(PANNumExceedMax);
			    }
				else
				{
					u8_counter=0 ;
					u8_flag =0;
					/* check if the PAN contains any characters */
					for (u8_counter=0;u8_counter<MAX_PAN_SIZE-1;u8_counter++)
					{
					    if (aStringBuffer[u8_counter] < 48 || aStringBuffer[u8_counter] > 58  )
					    {
						  APP_APPToTerminalResponse("The PAN must not contains any characters\r");
						  u8_flag =1;
						  break; // from for
					  }
					  
					}
					if (u8_flag==1)
					{
						continue;
					}
					else
					{
						APP_StoreDataEEPROM(aStringBuffer,PA_NUM);
						break;
					}
				}
			}
			
			
			while(1)
			{
				/* Display PIN Message */
				APP_APPToTerminalResponse(PINMessage);
				
				/* get Entered Data and check length */
				/* should be 4 characters */
				
				u8_MaxSize = APP_ReceiveFromTerminal();
				if (u8_MaxSize > MAX_PIN_SIZE || u8_MaxSize < MAX_PIN_SIZE )
				{
					APP_APPToTerminalResponse(PINNumExceedMax);
					
				}
				else
				{
					u8_counter=0 ;
					u8_flag =0;
					/* check if the PIN contains any characters */
					for (u8_counter=0;u8_counter<MAX_PIN_SIZE-1;u8_counter++)
					{
						if (aStringBuffer[u8_counter] < 48 || aStringBuffer[u8_counter] > 58  )
						{
							APP_APPToTerminalResponse("The PIN must not contains any characters\r");
							u8_flag =1;
							break; // from for
						}
						
					}
					if (u8_flag==1)
					{
						continue;
					}
					else
					{
						APP_StoreDataEEPROM(aStringBuffer,PIN);
						break;
					}
					
				}
				
			}
			
			
			
			/* Write the first loc 55 to indicate that the card is Programmed */
			ECUAL_EEPROMWrite(CARD_PROGRAMMED_CHECK_ADD,FIRST_LOC_Data);
			/* Enter User Mode */
			
			/* Copy data from EEPROM TO Data buffer */
			APP_ReadAllData();
			
			CurrentModeState = USER_MODE;
			APP_APPToTerminalResponse("Data updated successfully \r");
			APP_APPToTerminalResponse("user mode started \r");
			break;
		
	}
	 
}

}
/*********************************************************************************************/