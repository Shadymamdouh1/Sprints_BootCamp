/*****************************************************************************
* Module: BCM Module
* File Name: BCMCfg.c
* Description: Source file for BCM Module
* Author: Shady Mamdouh
* Date: 8/20/2021
******************************************************************************/
#include "BCMCfg.h"
#include "..\..\MCAL\UART Module\uart.h"
#include "..\..\Patterns\Interrupt Handler\ih_interface.h"
#include "BCM.h"

#define Device1MaxReq 100
#define Device2MaxReq 5
#define Device3MaxReq 5

BCMConfig_t DeviceArr[DeviceNum] =
     /*DeviceID*/             /*DeviceSendFunc */   /* DeviceReciveFunc*/   /*TX Vector ID */  /*RX Vector ID*/    /*MAX RQ */  
{
  {  UART_ID    ,  USART_Init   ,   USART_UpdateUDR ,      USART_GetUDR ,       USART_UDRE_INT , USART_RXC_INT,  Device1MaxReq }	
	
	
};