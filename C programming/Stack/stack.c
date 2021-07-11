/*
 * stack.c
 *
 *  Created on: Jul 11, 2021
 *      Author: Shady mamdouh
 */
#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include"Stack.h"


u8_t Stack_u8init(Sstack_control *str_stack, u8_t *pa_stackBuf,u8_t size)
{
	if(pa_stackBuf == NULL )
	{
		printf("Buffer is not exist\n");

		return 0;

	}
	else
	{
		str_stack->stack_ptr=pa_stackBuf;
		str_stack->size=size;
		str_stack->top=-1;
		return 1;
	}



}
u8_t Stack_u8Push(Sstack_control *str_stack,uint32_t au32_value)
{
	// check stack full
	if(str_stack->top == str_stack->size)
	{
		return 0;
	}
	else
	{
		str_stack->top++;
		str_stack->stack_ptr[str_stack->top]=au32_value;
		return 1;

	}
}
uint32_t Stack_u32Pop(Sstack_control *str_stack)
{
	uint32_t au_32Value;
	// check stack is empty
	if(str_stack->top==-1)
	{
		return 0;
	}
	else
	{
		au_32Value=str_stack->stack_ptr[str_stack->top];
		str_stack->top--;
		return au_32Value;
	}
}
u8_t String_syntax_check(u8_t *string,u8_t size)
{
	u8_t value;
	u8_t close1 ='{';
	u8_t close2 ='(';
	u8_t flag=0;
	Stack_u8init(&stack,Stak_buffer,SIZE);

	int i;
	for(i=0;i<10;i++)
	{
		if(string[i]=='{' || string[i]=='(' )
		{
			Stack_u8Push(&stack,string[i]);
			continue;

		}
		if(string[i]== '}')
		{
			value=Stack_u32Pop(&stack);
			if(value==-1)
			{
				printf("empty");
				fflush(stdin);fflush(stdout);
			}
			else
			{
				if (value == close1)
				{
					continue;
				}
				else
				{

					return 0;

				}
			}


		}
		if(string[i]== ')')
		{
			value=Stack_u32Pop(&stack);
			if(value==-1)
			{
				printf("empty");
				fflush(stdin);fflush(stdout);
			}
			else
			{
				if (value == close2)
				{
					continue;
				}
				else
				{

					return 0;
				}
			}
		}

	}
	if(flag == 0)
	{

		return 1;
	}
	return 0;
}
