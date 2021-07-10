/*
 * X_O.c
 *
 *  Created on: Jul 10, 2021
 *      Author: Shady mamdouh
 */
#include "compiler.h"
#include <stdio.h>
#include <stdlib.h>
// Reference array
u8_t Ref_array[3][3]={{'1','2','3'},{'4','5','6'},{'7','8','9'}};
// Image array
u8_t array[3][3];
//this function to display the game to user
void XO_voidDispay()
{

	u8_t au8_counter1;
	u8_t au8_counter2;
	printf("\n*************************");
				fflush(stdin);fflush(stdout);
	for(au8_counter1=0 ; au8_counter1<3 ; au8_counter1++)
	{
		printf("\n");
		fflush(stdin);fflush(stdout);
		for(au8_counter2=0 ; au8_counter2<3 ; au8_counter2++)
		{
			printf("%C\t",array[au8_counter1][au8_counter2]);
			fflush(stdin);fflush(stdout);
		}

	}
	printf("\n*************************\n");
}
u8_t XO_voidGetUserEntry(u8_t au8_player)
{
	u8_t *pu8_ptr=(u8_t *)array;
	u8_t au8_Entry;
	u8_t au8_location;
	printf("player [%c] : Enter Location : ",au8_player);
	fflush(stdin);fflush(stdout);
	scanf("%c",&au8_Entry);
	fflush(stdin);fflush(stdout);
	//test
	printf("%c ",au8_Entry);
		fflush(stdin);fflush(stdout);
	// convert from character to number
	au8_location =(au8_Entry-48)-1;
	// check if reserved location
	if(pu8_ptr[au8_location]=='X' || pu8_ptr[au8_location]=='O' )
	{
		printf("[ERROR] Reserved location");
			fflush(stdin);fflush(stdout);
			return 0;
	}
	else
	{
		pu8_ptr[au8_location]=au8_player;
		return 1;
	}
}
u8_t XO_WinCkeck(u8_t au8_player)
{
	if(     // rows check
			(array[0][0]== au8_player && array[0][1]== au8_player && array[0][2]== au8_player)
		|| (array[1][0]== au8_player && array[1][1]== au8_player && array[1][2]== au8_player)
		|| (array[2][0]== au8_player && array[2][1]== au8_player && array[2][2]== au8_player)
	      // column check
		||  (array[0][0]== au8_player && array[1][0]== au8_player && array[2][0]== au8_player)
		||  (array[0][1]== au8_player && array[1][1]== au8_player && array[2][1]== au8_player)
		||  (array[0][2]== au8_player && array[1][2]== au8_player && array[2][2]== au8_player)
		// cross check
		||  (array[0][0]== au8_player && array[1][1]== au8_player && array[2][2]== au8_player)
		||  (array[0][2]== au8_player && array[1][1]== au8_player && array[2][0]== au8_player)
	)
	{
		return 1;
	}


		return 0;

}
