/*
 ============================================================================
 Name        : Task02_Stack.c
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

int main(void) {

	u8_t string[10]="{5+(3))))}";
	if(String_syntax_check(string,10))
	{
		printf("balanced");
		fflush(stdin);fflush(stdout);
	}
	else
	{
		printf("Unbalanced");
	    fflush(stdin);fflush(stdout);
	}

	//print stack without popping but with the same order of poping

	Stack_u8Push(&stack,5);
	Stack_u8Push(&stack,6);
	Stack_u8Push(&stack,7);
	print_stack(&stack);




}


