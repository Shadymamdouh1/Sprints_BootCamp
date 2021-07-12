/*
 * Search_Alg.c
 *
 *  Created on: Jul 12, 2021
 *      Author: Shady mamdouh
 */
#include <stdio.h>
#include <stdlib.h>
#include "compiler.h"
#include "Search_Alg.h"
void SortArray(uint32_t *arr,uint8_t size)
{
	// Selection sorting
	uint32_t min_vlaue=arr[0];
	uint32_t min_index=0;
	uint8_t counter=0;
	uint32_t temp;
	uint8_t i;
	uint8_t flag =0;
	for(counter=0;counter<size;counter++)
	{
		min_vlaue=arr[counter];
		min_index=counter;
		for(i=(counter+1);i<size;i++)
		{
			if( arr[i]< min_vlaue )
			{
				min_vlaue = arr[i];
				min_index = i;
				flag=1;
			}


		}
		if(flag ==1)
		{
			temp = arr[counter];
			arr[counter]=arr[min_index];
			arr[min_index]=temp;
			flag=0;
		}
		else
		{
			continue;
		}

	}
}
sint8_t BinarySearch(uint32_t *arr , uint8_t size , uint32_t number)
{
	//uint8_t i;
	uint8_t mid;
	uint8_t start=0;
	uint8_t end;
	end = size-1;
	mid = (start+end)/2;

	while(start!=mid)
	{
		if(number == arr[mid])
		{
			return mid;
		}
		else if(number > arr[mid])
		{
			start=mid+1;
			mid = (start+end)/2;
		}
		else if(number < arr[mid])
		{
			end=mid-1;
			mid = (start+end)/2;
		}

	}
	if(mid==start)
	{
		if(number == arr[mid])
		{
			return mid;
		}
		else if(number == arr[end])

		{
			return end;
		}
	}
	return -1;



}
