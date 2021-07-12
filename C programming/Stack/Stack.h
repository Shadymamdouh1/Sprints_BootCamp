/*
 * Stack.h
 *
 *  Created on: Jul 11, 2021
 *      Author: HP
 */

#ifndef STACK_H_
#define STACK_H_
// stack buffer
u8_t Stak_buffer[10];
//u8_t Stak_buffer2[10];
#define SIZE 10
typedef struct Sstack
{
	s8_t top;
	u8_t *stack_ptr;
	u8_t size;
}Sstack_control ;
// stack
Sstack_control stack;
//APIs
u8_t Stack_u8init(Sstack_control *str_stack, u8_t *pa_stackBuf,u8_t size);
u8_t Stack_u8Push(Sstack_control *str_stack,uint32_t au32_value);
uint32_t Stack_u32Pop(Sstack_control *str_stack);
u8_t String_syntax_check(u8_t *string,u8_t size);
s8_t print_stack(Sstack_control *str_stack);
#endif /* STACK_H_ */
