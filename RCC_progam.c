/********************************************************/
/* Author     : shady mamdouh                           */
/* Version    : V01                                     */
/* Date       :                                         */
/********************************************************/

#include "STD_TYPES.h"
#include "BIT_MATH.h"
#include "RCC_interface.h"
#include "RCC_private.h"
#include "RCC_config.h"

void RCC_voidEnableClock(u8 Copy_u8BusId , u8 Copy_u8PerId )
{
	if(Copy_u8PerId <=31)
	{
		switch(Copy_u8BusId)
		{
		case RCC_AHB  :  SET_BIT(RCC->RCC_AHBENR  ,Copy_u8PerId);   break;
		case RCC_APB1 : SET_BIT(RCC->RCC_APB1ENR ,Copy_u8PerId);   break;
		case RCC_APB2 : SET_BIT(RCC->RCC_APB2ENR ,Copy_u8PerId);   break;
		//default       : /* return Error */  break;

		}

	}
	else
	{
		/* Return Error */
	}

}


void RCC_voidDisableClock(u8 Copy_u8BusId , u8 Copy_u8PerId )
{
	if(Copy_u8PerId <=31)
	{
		switch(Copy_u8BusId)
		{
		case RCC_AHB :  CLR_BIT(RCC->RCC_AHBENR  ,Copy_u8PerId);   break;
		case RCC_APB1 : CLR_BIT(RCC->RCC_APB1ENR ,Copy_u8PerId);   break;
		case RCC_APB2 : CLR_BIT(RCC->RCC_APB2ENR ,Copy_u8PerId);   break;
		//default       : /* return Error */  break;

		}

	}
	else
	{
		/* Return Error */
	}

}
void RCC_voidInitSysClock(void)
{
	/*Note according to TRM you should finish configuation before enable source */
#if      RCC_CLOCK_TYPE == RCC_HSE_CRYSTAL
	// Select HSE as a clock system SW :01
	RCC->RCC_CFGR |=((0b01) << 0);
	// Enable HSE
	SET_BIT(RCC->RCC_CR,16);
	// disable Bypass XTAL0 "by default disabled"
	CLR_BIT(RCC->RCC_CR,18);

#elif    RCC_CLOCK_TYPE == RCC_HSE_RC
	// Select HSE as a clock system SW :01
	RCC->RCC_CFGR |=((0b01) << 0);
	// Enable HSE
	SET_BIT(RCC->RCC_CR,16);
	// Enable Bypass XTAL0
	SET_BIT(RCC->RCC_CR,18);

#elif    RCC_CLOCK_TYPE == RCC_HSI

	// Select HSI as a clock system SW :00
	RCC->RCC_CFGR |=((0b00) << 0);
	// Enabe HSI
	SET_BIT(RCC->RCC_CR,0);


#elif    RCC_CLOCK_TYPE == RCC_PLL
	// Select PLL as a clock system SW :10
	RCC->RCC_CFGR |=((0b10) << 0);
	//Select PLL source
#if   RCC_PLL_INPUT == RCC_PLL_IN_HSI_DIV_2

#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE_DIV_2

#elif RCC_PLL_INPUT == RCC_PLL_IN_HSE

#endif


#else
#error("you chosed wrong clock type")
#endif
}
