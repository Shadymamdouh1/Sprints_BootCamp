/*
 ============================================================================
 Name        : Task01.c
 Author      : Shady mamdouh
 Version     :
 Copyright   : Your copyright notice
 Description : X-O application
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
  while(1)
  {
	  // Reinitialize the array

	  for(au8_counter1=0;au8_counter1<3;au8_counter1++)
	  {
		  for(au8_counter2=0;au8_counter2<3;au8_counter2++)
		  {
			  array[au8_counter1][au8_counter2]=Ref_array[au8_counter1][au8_counter2];
		  }
	  }



  while( !( XO_WinCkeck('X') || XO_WinCkeck('O') ) )
  {
	XO_voidDispay();
    while(!XO_voidGetUserEntry('X'));
    if(XO_WinCkeck('X'))
    {
    	printf("Player X is the winner\n");
    	XO_voidDispay();
    	fflush(stdin);fflush(stdout);
    	break;
    }
    XO_voidDispay();
    while(!XO_voidGetUserEntry('O'));
    if(XO_WinCkeck('O'))
    {
    	printf("Player O is the winner\n");
    	XO_voidDispay();
    	fflush(stdin);fflush(stdout);
    	break;
    }

  }
  printf("**************************\n");
  printf("Starting a new game ....\n");
  printf("***************************");
  fflush(stdin);fflush(stdout);
  }

}
