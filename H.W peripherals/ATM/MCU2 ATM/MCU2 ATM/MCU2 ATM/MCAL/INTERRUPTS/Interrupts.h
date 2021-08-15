/*
 * Interrupts.h
 *
 * Created: 8/7/2021 3:08:34 PM
 *  Author: Shady Mamdouh
 */ 
#include "types.h"

#ifndef INTERRUPTS_H_
#define INTERRUPTS_H_
#define LOW_LEVEL 0
#define Any_logic 1
#define Rising 2
#define Failing 3
#define ISC00 0
#define ISC01 1
#define ISC10 2
#define ISC11 3
#define ISC2 6
#define INT1 7
#define INT0 6
#define INT2 5
#define I 7

void EXTI0_init(uint8_t trigger);
void EXTI0_Enable(void);
void EXTI0_Disable(void);
void SetEXTI0CallBackFunction(void (*ptr)(void));

#endif /* INTERRUPTS_H_ */