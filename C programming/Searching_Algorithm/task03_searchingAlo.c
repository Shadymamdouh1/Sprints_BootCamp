/*
 ============================================================================
 Name        : task03_searchingAlo.c
 Author      : Shady mamdouh
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "Search_Alg.h"


int main(void){
    int i;
    sint8_t index;
    uint32_t number;
	uint32_t arr[5]={1,2,3,4,5};
	printf("Enter number to check");
			fflush(stdin);fflush(stdout);
			scanf("%d", &number);
			fflush(stdin);fflush(stdout);
	SortArray(arr,5);
	for(i=0;i<5;i++)
	{
		printf("%u \t", arr[i]);
		fflush(stdin);fflush(stdout);
	}
	printf("\n");
     fflush(stdin);fflush(stdout);

	index=BinarySearch(arr,5,number);
	if(index==-1)
	{
		printf("not found");
		fflush(stdin);fflush(stdout);
	}
	else
	{
		printf("the number is founded at location %d",index);
	    fflush(stdin);fflush(stdout);
	}
}
