/*
 * PaySystem.c
 *
 *  Created on: Jul 12, 2021
 *      Author: Shady Mamdouh
 */
#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "compiler.h"
#include "PaySystem.h"
//
uint8_t transaction_counter=0;
// maximum amount
#define MAX_AMOUNT 4000
//server data buffer
ST_accountBalance_t ServerDB[20] = {{"123456789",500.50},{"14765823",7600.25},{"987654321",5.50}};
// transaction data buffer
ST_Transaction_t Transaction_buffer[50];
// this function takes Card data
uint8_t GetCardData(ST_cardData_t *CardData)
{
	printf("Please Enter Card Data:\n");
	fflush(stdin);fflush(stdout);
	printf("Please Enter Card Holder Name:\n");
	fflush(stdin);fflush(stdout);
	gets(CardData->CardHolderName);
	printf("Please Enter Primary Account Number:\n");
	fflush(stdin);fflush(stdout);
	gets(CardData->PrimaryAccountNumber);
	printf("Please Enter Card Expiration Date in Format[MM/YY]:\n");
	fflush(stdin);fflush(stdout);
	gets(CardData->CardExpirationDate);


}


EN_TransState_t GetTerminalData(ST_TerminalData_t *TerData,ST_cardData_t *CardData)
{
	TerData->MaxtransAmount=MAX_AMOUNT;
	printf("Please Enter Terminal Data:\n");
	fflush(stdin);fflush(stdout);
	printf("Please Enter The Transaction Amount :\n");
	fflush(stdin);fflush(stdout);
	scanf("%f",&TerData->transAmount);
	fflush(stdin);fflush(stdout);
	// check max amount
	if(TerData->MaxtransAmount < TerData->transAmount)
	{
		return DECLINED;
	}
	printf("Please Enter Transaction Date:\n");
	fflush(stdin);fflush(stdout);
	gets(TerData->TransactionDate);
	// compare dates
	// tens digit in years
	if(CardData->CardExpirationDate[3] < TerData->TransactionDate[8])
	{
		return DECLINED;
	}
	else if(CardData->CardExpirationDate[3]==TerData->TransactionDate[8])
	{
		// ones digit in years
		if(CardData->CardExpirationDate[4] < TerData->TransactionDate[9])
		{
			return DECLINED;
		}
		else if(CardData->CardExpirationDate[4]==TerData->TransactionDate[9])
		{
			// tens digit in months
			if(CardData->CardExpirationDate[0]<TerData->TransactionDate[3])
			{
				return DECLINED;
			}
			else if(CardData->CardExpirationDate[0]==TerData->TransactionDate[3])
			{
				//ones digit in month
				if(CardData->CardExpirationDate[1]<TerData->TransactionDate[4])
				{
					return DECLINED;
				}
			}

		}
	}

//return 1;

}
EN_TransState_t Server_check(ST_TerminalData_t *TerData,ST_cardData_t *CardData)
{
	uint8_t counter;
	for(counter=0;counter<10;counter++)
	{
		if(strcmp(ServerDB[counter].PrimaryAccountNumber, CardData->PrimaryAccountNumber)==0)
		{   // check for enough balance
			if(ServerDB[counter].Balance > TerData->transAmount)
			{
				ServerDB[counter].Balance = (ServerDB[counter].Balance )- (TerData->transAmount);
				// print new balance
				printf("*********************\n");
				fflush(stdin);fflush(stdout);
				printf("the new balance is :%.2f\n",ServerDB[counter].Balance);
				fflush(stdin);fflush(stdout);
				return APPROVED;

			}
			else
			{
				return DECLINED;
			}
		}
	}
	// NOT Founded
	return DECLINED;
}

void Save_Transaction_Data(ST_TerminalData_t *TerData,ST_cardData_t *CardData,EN_TransState_t status)
{
	Transaction_buffer[transaction_counter].CardHolderData=*CardData;
	Transaction_buffer[transaction_counter].TransData=*TerData;
	Transaction_buffer[transaction_counter].TransStat=status;
	transaction_counter++;
	// if the buffer full overwrite from the first location
	if(transaction_counter==49)
	{
		transaction_counter=0;
	}
}
void Print_transaction_Data(void)
{
	uint8_t i;
for(i=0;i<transaction_counter;i++)
{

	printf("*********************\n");
    fflush(stdin);fflush(stdout);
    printf("Transaction Data :\n");
        fflush(stdin);fflush(stdout);
	printf("transaction[%d] :\n",i);
	fflush(stdin);fflush(stdout);
	printf("Name :%s \n",Transaction_buffer[i].CardHolderData.CardHolderName);
	fflush(stdin);fflush(stdout);
	printf("Primary Account Number :%s \n",Transaction_buffer[i].CardHolderData.PrimaryAccountNumber);
	fflush(stdin);fflush(stdout);
	printf("Expiration Date: %s \n",Transaction_buffer[i].CardHolderData.CardExpirationDate);
	fflush(stdin);fflush(stdout);

	printf("Transaction Amount: %.2f \n",Transaction_buffer[i].TransData.transAmount);
	fflush(stdin);fflush(stdout);
	printf("Max Amount: %.2f \n",Transaction_buffer[i].TransData.MaxtransAmount);
	fflush(stdin);fflush(stdout);
	printf("Transaction Date: %s \n",Transaction_buffer[i].TransData.TransactionDate);
	fflush(stdin);fflush(stdout);
	if(Transaction_buffer[i].TransStat == DECLINED)
	{
		printf("Status : DECLINED \n");
		fflush(stdin);fflush(stdout);
	}
	else
	{
		printf("Status : APPROVED\n");
	    fflush(stdin);fflush(stdout);
	}


	printf("*********************\n");
	fflush(stdin);fflush(stdout);
}
}




