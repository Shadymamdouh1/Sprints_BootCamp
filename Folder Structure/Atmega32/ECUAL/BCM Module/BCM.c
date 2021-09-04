/*****************************************************************************
* Module: BCM Module
* File Name: BCM.h
* Description: Header file for BCM Module
* Author: Shady Mamdouh
* Date: 8/20/2021
******************************************************************************/

/******************************INCLUDES************************************/
#include "..\..\Microcontroller\Platform_Types.h"
#include "..\..\Microcontroller\Std_types.h"
#include "..\..\Microcontroller\Atmega32 Registers\Dio_regs.h"
#include "..\..\Patterns\Interrupt Handler\ih_interface.h"
#include "..\..\MCAL\UART Module\uart.h"

#include "BCMCfg.h"
#include "BCM.h"
/************************************************************************/

#define Device1 0U
#define Device2 1U
#define Device3 2U
/*************************************************************************/
#define INITIALIZED				0U
#define NOT_INITIALIZED			1U
/**************************Device States**************************************/
#define Idle				    0U
#define TxMode				    1U
#define RxMode				    2U
#define SendingByte			    3U
#define RdyForSendNewByte       4U
#define RecevingByte            5U
#define RdyForReceiveNewByte    6U
uint8_t DeviceMode[DeviceNum];
/*****************************************************************************/
#define  HeaderLenght 6
/*****************************************************************************/

#define MAX_Allowed_RQ     100U
uint8_t MAX_RQ_NUM[DeviceNum]={MAX_Allowed_RQ} ; /* the max number of requests allowed*/
uint8_t Current_RQ_NUM[DeviceNum] ;   /* the number of current requests */
//uint16_t DevicesCounters[DeviceNum] ;   /* counters of transmitting bytes*/
uint8_t RQCounter[DeviceNum];
uint8_t CurrentRQHandling [DeviceNum];
BCMPtr_t ArrOfTXCallback[DeviceNum]={Device1TXCallBackFun};
BCMPtr_t ArrOfRXCallback[DeviceNum]={Device1RXCallBackFun};
/******************************************************************************/
static uint8_t Pattern[4]={'A','B','C','D'};
/*************************************************************************/
typedef struct BCM_RQ_t
{
	uint8_t * Buffer;
	uint8_t BufferSize;
	BCMPtr_t BCM_CallBackFunction;
	
	}BCM_RQ_t;
typedef struct BCM_RXBufferConfig_t
{
	uint8_t * Buffer;
	uint8_t BufferSize;
}BCM_RXBufferConfig_t;

/* TX Request arrays */	
BCM_RQ_t DeviceReqArr[DeviceNum][MAX_Allowed_RQ];
/* RX buffer setting */
BCM_RXBufferConfig_t DeviceRxBuffersSet[DeviceNum]	;
/* Rx buffer state that informs if the RX received a frame or not */
uint8_t DeviceRxBuffersState[DeviceNum];

/****************************Buffers***************************************/
#define  MAX_buffur_SIZE 100
uint8_t  RxBuffer[DeviceNum][MAX_buffur_SIZE]; /* Buffer for each Device */
uint16_t RxBufferCounter[DeviceNum];  
uint8_t  TxBuffer[DeviceNum][MAX_buffur_SIZE];
uint16_t TxBufferCounter[DeviceNum]={0};
/***************************States****************************************/
uint8_t BCMInitState = NOT_INITIALIZED;
/*****************************************************************************************
* Parameters (in): None
* Parameters (out):BCM_Return_t
* Return value: None
* Description: BCM Initialize function 
******************************************************************************************/
BCM_Return_t BCM_Init(void)
{
	
	//USART_Init();
	
	


	if (BCMInitState==NOT_INITIALIZED)
	{
		uint8_t u8_counter =0;
		for (u8_counter=0;u8_counter<DeviceNum;u8_counter++)
		{
			if(DeviceArr[u8_counter].DeviceInitFunc != NULL_PTR)
			{
				/* Initializing Devices */
				DeviceArr[u8_counter].DeviceInitFunc();
			}
		}
		
		BCMInitState = INITIALIZED;
	}
	return BCM_ERROR_OK;
	
}
/*****************************************************************************************
* Parameters (in): BCMIn_Device , SendBuffer ,SendBufferSize
* Parameters (out):BCM_Return_t
* Return value: None
* Description: This Function used by App to request sending by specific device
******************************************************************************************/
BCM_Return_t BCM_SendRQ(uint8_t BCMIn_Device,uint8_t *SendBuffer,uint16_t SendBufferSize,BCMPtr_t CallBackFun)
{
	/*************************Safety Handling******************************************/
	if (BCMIn_Device >= DeviceNum )
	{
		return BCM_WrongDevice ;
	}
	if (SendBuffer==NULL_PTR)
	{
		return BCM_InvalidPointer;
	}
	if (CallBackFun==NULL_PTR)
	{
		return BCM_InvalidPointer;
	}
	/********************************************************************************/
	/* check Max requests */
	if (Current_RQ_NUM[BCMIn_Device]== MAX_RQ_NUM[BCMIn_Device])
	{
		return BCM_Request_Rejected;
	}
	else
	{
		
		/* Assign Call back function */
		DeviceReqArr[BCMIn_Device][RQCounter[BCMIn_Device]].BCM_CallBackFunction = CallBackFun;
		/* Assign Buffer */
		DeviceReqArr[BCMIn_Device][RQCounter[BCMIn_Device]].Buffer = SendBuffer;
		/* Assign Buffer Size */
		DeviceReqArr[BCMIn_Device][RQCounter[BCMIn_Device]].BufferSize = SendBufferSize;
		/* Increment the Number of Requests of this device */
		Current_RQ_NUM[BCMIn_Device]++;
		RQCounter[BCMIn_Device]++;
		if (RQCounter[BCMIn_Device]==MAX_RQ_NUM[BCMIn_Device])
		{
			
				RQCounter[BCMIn_Device]=0;
			
			
		}
		return BCM_Request_Accept;
	}
		
}
	
/*******************************************************************************************/
/*****************************************************************************************
* Parameters (in): BCMIn_Device , ReceiveBuffer ,ReceiveBufferSize
* Parameters (out):BCM_Return_t
* Return value: BCM_Return_t
* Description: This Function used by App to establish RX buffer 
******************************************************************************************/
BCM_Return_t BCM_RXSetBuffer(uint8_t BCMIn_Device,uint8_t *ReceiveBuffer,uint16_t ReceiveBufferSize)
{
	
	/*************************Safety Handling******************************************/
	if (BCMIn_Device >= DeviceNum )
	{
		return BCM_WrongDevice ;
	}
	if (ReceiveBuffer==NULL_PTR)
	{
		return BCM_InvalidPointer;
	}
	
	/********************************************************************************/
	/* Setting RX buffer */
	DeviceRxBuffersSet[BCMIn_Device].Buffer =    ReceiveBuffer;
	DeviceRxBuffersSet[BCMIn_Device].BufferSize =ReceiveBufferSize;
	return RX_BufferSet;
}
/*****************************************************************************************
* Parameters (in): BCMIn_Device , ReceiveBuffer ,ReceiveBufferSize
* Parameters (out):BCM_Return_t
* Return value: BCM_Return_t
* Description: This Function is the call back function for RX device1 
******************************************************************************************/
#define Rx_FrameValid 0
#define Rx_FrameINValid 1
uint8_t RecivedFramValidation[DeviceNum] ;
uint16_t RxReceivedSize[DeviceNum];
void Device1RXCallBackFun(void)
{
	/*update Device  mode*/
	DeviceMode[Device1]=RxMode ;
	 /* Receive the first 6 bytes to check the BCM pattern and size */
	 if (RxBufferCounter[Device1] <= 6)
	 {
		 uint8_t ReceivedByte ;
		 /* Call the receiver function of the device */
		 DeviceArr[Device1].DeviceReciveFunc(&ReceivedByte);
		 /* save the data into the RX buffer of the device */
		 RxBuffer[Device1][RxBufferCounter[Device1]]=ReceivedByte;
		 
		 /* Increment the device RX  counter*/
		 
		 RxBufferCounter[Device1]++;
		 
		 if (RxBufferCounter[Device1]==6)
		 {
			 
			 /* Check the pattern */
			 uint8_t u8_counter =0;
			 for(u8_counter=0;u8_counter<4;u8_counter++)
			 {
				 if (RxBuffer[Device1][u8_counter] != Pattern[u8_counter])
				 {
					 RecivedFramValidation[Device1] = Rx_FrameINValid;
					 break;
				 }
			 }
			 if (RecivedFramValidation[Device1] == Rx_FrameValid)
			 {
				 /* Get size */
				 RxReceivedSize[Device1]=0;
				 RxReceivedSize[Device1]  =(8<< RxBuffer[Device1][4]) ;
				 RxReceivedSize[Device1] |=RxBuffer[Device1][5];
			 }
			 
		 }
		 
		 
		 
	 }
	
	else if (RxBufferCounter[Device1]>6)
	{
		if (RecivedFramValidation[Device1] == Rx_FrameValid)
		{
			/*Check if receiving complete */
			if (RxBufferCounter[Device1]==RxReceivedSize[Device1] + HeaderLenght-1)
			{
				
				uint8_t ReceivedByte ;
				/* Call the receiver function of the device */
				DeviceArr[Device1].DeviceReciveFunc(&ReceivedByte);
				/* save the data into the RX buffer of the device */
				RxBuffer[Device1][RxBufferCounter[Device1]]=ReceivedByte;
				/* Increment the device RX  counter*/
				RxBufferCounter[Device1]++;
				
				
				
				/* Reset counter */
				RxBufferCounter[Device1]=0;
				/* Update Device State */
				DeviceMode[Device1] =Idle;
				/*reset the RX state */
				RecivedFramValidation[Device1] = Rx_FrameValid;
				/*Update RX buffer state to Data has been received */
				DeviceRxBuffersState[Device1]=RECEIVED_DATA;
				/*copy the data from RX buffer to app buffer*/
				uint8_t counter1=0;
				uint8_t counter2=6;
				for(counter1=0;counter1<DeviceRxBuffersSet[Device1].BufferSize;counter1++)
				{
					DeviceRxBuffersSet[Device1].Buffer[counter1] =  RxBuffer[Device1][counter2];
					counter2++;
				}
				/*Stop RX */
				IH_Deinstall(DeviceArr[Device1].DeviceRxVectorID);
				
				
			}
			else
			{
				uint8_t ReceivedByte ;
				/* Call the receiver function of the device */
				DeviceArr[Device1].DeviceReciveFunc(&ReceivedByte);
				/* save the data into the RX buffer of the device */
				RxBuffer[Device1][RxBufferCounter[Device1]]=ReceivedByte;
				/* Increment the device RX  counter*/
				RxBufferCounter[Device1]++;
				
				
			}
		}
		else
		{
			/* Reset counter */
			RxBufferCounter[Device1]=0;
			/* Update Device State */
			DeviceMode[Device1] =Idle;
			/*reset the RX state */
			RecivedFramValidation[Device1] = Rx_FrameValid;
			/* Ignore the frame if it is not valid frame  */
			
			/*Stop RX */
			IH_Deinstall(DeviceArr[Device1].DeviceRxVectorID);
		}
	}
	
	
}
void Device1TXCallBackFun(void)
{
	
	
	
	
	/* Check if Buffer Transmit Complete */ 
	if (TxBufferCounter[Device1] > ( (DeviceReqArr[Device1][CurrentRQHandling[Device1]].BufferSize)-1 + HeaderLenght)   )
	{
		
		/* reset counter */
		TxBufferCounter[Device1] =0;
		/* Update Device State */
		DeviceMode[Device1] =Idle;
		/*Decrement the Number of requests */
		Current_RQ_NUM[Device1]--;
		/* Inform the user that transmission is done */
		DeviceReqArr[Device1][CurrentRQHandling[Device1]].BCM_CallBackFunction();
		/* Reset the request location */
		DeviceReqArr[Device1][CurrentRQHandling[Device1]].BCM_CallBackFunction=NULL_PTR;
		/* de install on UDRE Interrupt */
		//IH_Deinstall(USART_UDRE_INT);
		IH_Deinstall(DeviceArr[Device1].DeviceTxVectorID);
		
		CurrentRQHandling[Device1]++;
		if (CurrentRQHandling[Device1]==MAX_RQ_NUM[Device1])
		{
			CurrentRQHandling[Device1]=0;
		}
		
	}
	else
	{
		uint8_t u8_temp = ( TxBuffer[Device1][TxBufferCounter[Device1]] );
		DeviceArr[Device1].DeviceSendFunc(&u8_temp);
		TxBufferCounter[Device1]++;
		
		
	}
	 
}
void Device2CallBackFun(void)
{
	
}
void Device3CallBackFun(void)
{
	
}
/*****************************************************************************************
* Parameters (in): None 
* Parameters (out):None
* Return value: None
* Description: The main function of UART TX
******************************************************************************************/
void BCM_Mainfunction(void)
{
	uint8_t u8_DeviceCounter =0;
	
	for (u8_DeviceCounter=0;u8_DeviceCounter<DeviceNum;u8_DeviceCounter++)
	{
		if (DeviceMode[u8_DeviceCounter]==Idle)
		{
			/* Enable Device  Rx */
			InterruptHandlerConfig_t config ;
			/* Enable RX Interrupt for the Device */
			config.u8_InIHVectorNum =DeviceArr[u8_DeviceCounter].DeviceRxVectorID;
			IH_Install(&config,ArrOfRXCallback[u8_DeviceCounter]);
			
			/*check if TX  need to be handled*/
			/* Check if there are requests that not handled */ 
			if (Current_RQ_NUM[u8_DeviceCounter] !=0)
			{
				/* Disable RX during TX handling */
				
				IH_Deinstall(DeviceArr[Device1].DeviceRxVectorID);
				/* Lock The device to handle the request */
				DeviceMode[u8_DeviceCounter]=TxMode ;
				/* handle the request with it's Index in the Requests array */
				
				/* handle the request */
				TXRQHandler(u8_DeviceCounter,CurrentRQHandling[u8_DeviceCounter]);
				
				break;
					
			}
					
				
			}
			
		}
		 
		
}
/**************************************************************************************/

/****************************************************************************************/
void TXRQHandler(uint8_t DeviceId,uint8_t RQId )
{
	uint8_t u8_counter=0;
	uint8_t u8_counter2=6;
	uint16_t u16_size;
	
	/*Add BCM Command Pattern */
	for (u8_counter=0;u8_counter<4;u8_counter++)
	{
		TxBuffer[DeviceId][u8_counter]=Pattern[u8_counter];
	}
	u16_size= DeviceReqArr[DeviceId][RQId].BufferSize;
	TxBuffer[DeviceId][4]=(uint8_t)(u16_size>>8);
	TxBuffer[DeviceId][5]=(uint8_t)u16_size;
	for (u8_counter=0;u8_counter<u16_size;u8_counter++)
	{
		TxBuffer[DeviceId][u8_counter2]=DeviceReqArr[DeviceId][RQId].Buffer[u8_counter];
		u8_counter2++;
	}
	
	
	InterruptHandlerConfig_t config ;
	/* Enable Tx Interrupt for the Device */
	config.u8_InIHVectorNum =DeviceArr[DeviceId].DeviceTxVectorID;
	IH_Install(&config,ArrOfTXCallback[DeviceId]);
	
	
}
/*****************************************************************************************/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out):None
* Return value: None
* Description: The main function of UART TX
******************************************************************************************/
BCM_Return_t BCM_GetRXBufferState(uint8_t DeviceId,   uint8_t *state)
{
	/*******************Safety handling ******************************/
	if (DeviceId>Device3)
	{
		return BCM_WrongDevice;
	}
	if (state==NULL_PTR)
	{
		return BCM_InvalidPointer;
	}
	/*************************************************************************************/
	     *state =DeviceRxBuffersState[DeviceId];
		 
		 /* reset state for next receiving */
		 DeviceRxBuffersState[DeviceId] = NO_RECEIVED_DATA;
		 
}