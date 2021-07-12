/*
 ============================================================================
 Name        : task02_stack_test.c
 Author      : Shady mamdouh
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include"Stack.h"


u8_t push_test()
{
	Stack_u8Push(&stack,5);
	if(Stak_buffer[0]==5)
	{
		return 1;
	}
	else return 0;
}
u8_t pop_test()
{  u8_t value;
value=Stack_u32Pop(&stack);
if(value==5)
{
	return 1;
}
else
{
	return 0;
}
}
// text check
u8_t text_test(u8_t *string)
{

	if(String_syntax_check(string,10))
	{
		printf("balanced\n");
		fflush(stdin);fflush(stdout);
		return 1;
	}
	else
	{
		printf("Unbalanced\n");
		fflush(stdin);fflush(stdout);
		return 2;
	}
}
void Print_stack_test()
{
	Stack_u8Push(&stack,5);
	Stack_u8Push(&stack,6);
	Stack_u8Push(&stack,7);
	print_stack(&stack);
}
int main(void) {
	Stack_u8init(&stack,Stak_buffer,SIZE);
	/*test case 1
	 * function Stack_u8Push
	 *
	 */
	if(push_test())
	{
		printf("passed\n");
	}
	else
	{
		printf("failed\n");
	}

	/*test case 2
	 *
	 */
	if(pop_test())
	{
		printf("passed\n");
	}
	else
	{
		printf("failed\n");
	}
	/*test case 3
	 *
	 */
	u8_t string[10]="{5+(3)}";
	if(text_test(string))
	{
		printf("passed\n");
	}
	else
	{
		printf("failed\n");
	}
	/*test case 4
		 *
		 */
	u8_t string1[10]="{5+(3))))}";
	if(text_test(string1)==2)
		{
			printf("passed\n");
		}
		else
		{
			printf("failed\n");
		}
	//test case 5
	//print stack without popping but with the same order of poping
	Print_stack_test();

}
