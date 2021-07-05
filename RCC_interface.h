/********************************************************/
/* Author     : shady mamdouh                           */
/* Version    : V01                                     */
/* Date       :                                         */
/********************************************************/

#ifndef _RCC_INTERFACE_H
#define _RCC_INTERFACE_H
// BUSES
#define RCC_AHB            0 
#define RCC_APB1           1
#define	RCC_APB2           2
//Peripherals bit number
#define AHB_DMA1 0
#define AHB_DMA2 1

#define APB2_AFIO 0
#define APB2_IOPA 2
#define APB2_IOPB 3
#define APB2_IOPC 4
#define APB2_TIM1 11
#define APB2_EXTI

#define APB1_TIM2 0

// APIs
void RCC_voidEnableClock(u8 Copy_u8BusId , u8 Copy_u8PerId );
void RCC_voidDisableClock(u8 Copy_u8BusId , u8 Copy_u8PerId );
void RCC_voidInitSysClock(void);
#endif
