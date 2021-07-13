/*
 ============================================================================
 Name        : PaymentSystem.c
 Author      : Shady mamdouh
 Version     :
 Copyright   : Your copyright notice
 Description : Hello World in C, Ansi-style
 ============================================================================
 */

#include <stdio.h>
#include <stdlib.h>
#include "string.h"
#include "compiler.h"
#include "PaySystem.h"
int main(void) {
	//Y or N
	uint8_t confirm='Y';
	ST_cardData_t CardData;
	ST_TerminalData_t TerminalData;

	while(confirm=='Y')
	{
		GetCardData(&CardData);
		if(GetTerminalData(&TerminalData,&CardData)==DECLINED)
		{
			printf("The Transaction is Declined \n");
			Save_Transaction_Data(&TerminalData,&CardData,DECLINED);
		}

		else if(Server_check(&TerminalData,&CardData)==DECLINED)
		{   printf("Verifying Data from the server \n");
			printf("The Transaction is Declined\n");
			Save_Transaction_Data(&TerminalData,&CardData,DECLINED);
		}
		else
		{
			printf("The Transaction is APPROVED\n");
			Save_Transaction_Data(&TerminalData,&CardData,APPROVED);
		}

		printf("Do you Want to continue[Y or N]\n");
		fflush(stdin);fflush(stdout);
		scanf("%c",&confirm);

	}
	Print_transaction_Data();
}
