/*****************************************************************************
* Module: BCM Module
* File Name: BCM.h
* Description: Header file for BCM Module
* Author: Shady Mamdouh
* Date: 8/20/2021
******************************************************************************/


#ifndef BCM_H_
#define BCM_H_
#include "..\..\Microcontroller\Platform_Types.h"
#include "..\..\Microcontroller\Std_types.h"
#include "BCMCfg.h"
typedef void(*BCMPtr_t)(void) ;
typedef int(*BCMPtr2_t)(void) ;
//typedef (int)(*initPtr_t)(void);
typedef void(*BCMCommFunc)(uint8_t *IO_Data);
typedef struct BCMConfig_t
{
	uint8_t     DeviceID;
	BCMPtr2_t    DeviceInitFunc;
	BCMCommFunc DeviceSendFunc;
	BCMCommFunc DeviceReciveFunc;
	uint8_t		DeviceTxVectorID ;
	uint8_t     DeviceRxVectorID;
	uint8_t     DeviceMaxRequests;
}BCMConfig_t;



#define UART_TX_Buffer_SIZE 100U
#define UART_RX_Buffer_SIZE 100U
#define UART_ID				0U
#define SPI_ID				1U
#define I2C_ID				2U
/* Rx buffer state that informs if the RX received a frame or not */
#define RECEIVED_DATA  1U
#define NO_RECEIVED_DATA 0U
typedef enum BCM_Return_t
{
	BCM_ERROR_OK,
	BCM_Request_Rejected,
	BCM_Request_Accept,
	BCM_WrongDevice,
	RX_BufferSet,
	BCM_InvalidPointer,	
}BCM_Return_t;

BCM_Return_t BCM_Init(void);
BCM_Return_t BCM_SendRQ(uint8_t BCMIn_Device,uint8_t *SendBuffer,uint16_t SendBufferSize,BCMPtr_t CallBackFun);
BCM_Return_t BCM_RXSetBuffer(uint8_t BCMIn_Device,uint8_t *ReceiveBuffer,uint16_t ReceiveBufferSize);
BCM_Return_t BCM_GetRXBufferState(uint8_t DeviceId,   uint8_t *state);
void BCM_Mainfunction(void);
void Device1RXCallBackFun(void);
void Device1TXCallBackFun(void);
void TXRQHandler(uint8_t DeviceId,uint8_t RQId );
extern BCMConfig_t DeviceArr[DeviceNum];
#endif /* BCM_H_ */