/*
 ============================================================================
 Name        : c.c
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
uint8_t sorting_test(uint32_t *array)
{  uint8_t i;
SortArray(array,5);
for(i=0;i<5;i++)
{
	printf("%u \t", array[i]);
	fflush(stdin);fflush(stdout);
}
if(array[0]==1)
{
	return 1;
}
else
{
	return 0;
}
}
sint8_t Binary_Search_test(uint32_t *array,uint32_t number)
{  uint8_t index;
index=BinarySearch(array,5,number);
return index;
}
int main(void) {
	uint32_t arr[5]={2,1,5,4,3};
	// test case 1
	if(sorting_test(arr))
	{
		printf("Pass\n");
		fflush(stdin);fflush(stdout);
	}
	else
	{
		printf("failed\n");
		fflush(stdin);fflush(stdout);
	}
	// test case 2
	if(Binary_Search_test(arr,3)==2)
	{
		printf("Pass\n");
		fflush(stdin);fflush(stdout);
	}
	else
	{
		printf("failed\n");
		fflush(stdin);fflush(stdout);
	}
	// test case 3
		if(Binary_Search_test(arr,20)==-1)
		{
			printf("Pass\n");
			fflush(stdin);fflush(stdout);
		}
		else
		{
			printf("failed\n");
			fflush(stdin);fflush(stdout);
		}
}
