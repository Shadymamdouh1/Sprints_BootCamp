/********************************************************/
/* Author     : shady mamdouh                           */
/* Version    : V01                                     */
/* Date       :                                         */
/********************************************************/

#ifndef _RCC_PRIVATE_H
#define _RCC_PRIVATE_H

#define RCC_BASE 0x40021000
//register definitions

typedef struct {
	u32 RCC_CR ;
	u32 RCC_CFGR ;
	u32 RCC_CIR ;
	u32 RCC_APB2RSTR ;
	u32 RCC_APB1RSTR ;
	u32 RCC_AHBENR ;     // enable clock for AHB peripherals
	u32 RCC_APB2ENR ;    // enable clock for APB2 peripherals
	u32 RCC_APB1ENR ;    // enable clock for APB1 peripherals
	u32 RCC_BDCR ;
	u32 RCC_CSR ;
} RCC_REG;

#define RCC ((RCC_REG *)RCC_BASE)

/* Clock Typers*/
#define RCC_HSE_CRYSTAL 0
#define RCC_HSE_RC      1
#define RCC_HSI         2
#define RCC_PLL         3
#endif 
/* PLL Options */
#define RCC_PLL_IN_HSI_DIV_2   0
#define RCC_PLL_IN_HSE_DIV_2   1
#define RCC_PLL_IN_HSE         2
