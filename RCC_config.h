/********************************************************/
/* Author     : shady mamdouh                           */
/* Version    : V01                                     */
/* Date       : 5/7/2021                                        */
/********************************************************/

#ifndef _RCC_CONFIG_H
#define _RCC_CONFIG_H
/* Options : RCC_HSE_CRYSTAL
           : RCC_HSE_RC
		   : RCC_HSI
		   : RCC_PLL
 */
#define RCC_CLOCK_TYPE RCC_HSI

/* Options : RCC_PLL_IN_HSI_DIV_2
           : RCC_PLL_IN_HSE_DIV_2
		   : RCC_PLL_IN_HSE     */

/* Note : Select value only if you have PLL as input clock source */
#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_INPUT RCC_PLL_IN_HSI_DIV_2
#endif

/* Note : Select value only if you have PLL as input clock source */
/* Options 2 to 16  */
#if RCC_CLOCK_TYPE == RCC_PLL
#define RCC_PLL_MUL_VAL
#endif


#endif
