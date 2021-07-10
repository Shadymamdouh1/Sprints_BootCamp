/*
 ============================================================================
 Name        : Task01.c
 Author      : Shady mamdouh
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "X_O.h"
extern u8_t Ref_array[3][3];
extern u8_t array[3][3];
int main(void) {
	u8_t au8_counter1;
		u8_t au8_counter2;


		  // Reinitialize the array

		  for(au8_counter1=0;au8_counter1<3;au8_counter1++)
		  {
			  for(au8_counter2=0;au8_counter2<3;au8_counter2++)
			  {
				  array[au8_counter1][au8_counter2]=Ref_array[au8_counter1][au8_counter2];
			  }
		  }
	int i;
	/**********************************************************************/
	/* test case 1
	 * function tested :XO_voidDispay();
	 * this function displays the content of the array
	 * Expected output :
	 * 				   1	2	3
	 * 				   4    5   6
	 * 				   7    8   9
	 * 	Actual output :
	 * 				   1	2	3
	 * 				   4    5   6
	 * 				   7    8   9
	 * 	passed
	 */
	XO_voidDispay();
	/********************************************************************/

	/* test case 2
	 * function :XO_voidDispay();
	 * XO_voidGetUserEntry('X');
	 * this function takes location from user and replace it by X or O according to the argument
	 * we will assign X in location [0][0]
	 * as a user will enter location 1
	 * Expected output :
	 * 				   X	2	3
	 * 				   4    5   6
	 * 				   7    8   9
	 * 	Actual output :
	 * 				   X	2	3
	 * 				   4    5   6
	 * 				   7    8   9
	 * 	passed
	 *
	 * */
	XO_voidGetUserEntry('X');
	XO_voidDispay();
	/*********************************************************************/
	/* test case 3
		 * function :XO_WinCkeck('O');
		 *
		 * this function will check if any entire row or column or cross totally consists of O's
		 *
		 * first we should assign an entire row with O
		 *
		 * 				   1	2	3
		 * 				   O    O   O
		 * 				   7    8   9
		 * 	expected output returns 1
		 * 	Actual output : returns 1
		 *
		 * 	passed
		 *
		 * */
	//first we should assign an entire row with O
	array[1][0]='O';
	array[1][1]='O';
	array[1][2]='O';
	if(XO_WinCkeck('O'))
	{
		XO_voidDispay();
		printf("Pass");
	}
	else
	{   XO_voidDispay();
		printf("Fail");
	}
}
