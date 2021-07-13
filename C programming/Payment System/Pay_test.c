/*
 ============================================================================
 Name        : Pay_test.c
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
typedef enum test_t
{
	PASS,
	FAILED
}test_t;
test_t test_status;
test_t Approve_test()
{
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
			printf("Verifying Data from the server \n");
			if(Server_check(&TerminalData,&CardData)==DECLINED)
			{
				printf("The Transaction is Declined\n");
				Save_Transaction_Data(&TerminalData,&CardData,DECLINED);
			}
			else
			{
				printf("The Transaction is APPROVED\n");
				Save_Transaction_Data(&TerminalData,&CardData,APPROVED);
				//test case check
				return PASS;
			}

			printf("Do you Want to continue[Y or N]\n");
			fflush(stdin);fflush(stdout);
			scanf("%c",&confirm);

		}
		//Print_transaction_Data();
		return FAILED;
}
test_t Declined_test_expired_card()
{
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
				//test case check
				return PASS;
			}
			printf("Verifying Data from the server \n");
			if(Server_check(&TerminalData,&CardData)==DECLINED)
			{
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
		//Print_transaction_Data();
		return FAILED;
}
test_t Declined_test_noEnough_Balance()
{
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
				printf("Verifying Data from the server \n");
				if(Server_check(&TerminalData,&CardData)==DECLINED)
				{
					printf("The Transaction is Declined\n");
					Save_Transaction_Data(&TerminalData,&CardData,DECLINED);
					//test case check
				    return PASS;
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
			//Print_transaction_Data();
			return FAILED;
}
test_t Declined_test_Fack_ACC_number()
{
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
				printf("Verifying Data from the server \n");
				if(Server_check(&TerminalData,&CardData)==DECLINED)
				{
					printf("The Transaction is Declined\n");
					Save_Transaction_Data(&TerminalData,&CardData,DECLINED);
					//test case check
				    return PASS;
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
			//Print_transaction_Data();
			return FAILED;
}
test_t Declined_test_exceedMax_amount()
{
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
					//test case check
					 return PASS;

				}
				printf("Verifying Data from the server \n");
				if(Server_check(&TerminalData,&CardData)==DECLINED)
				{
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
			//Print_transaction_Data();
			return FAILED;
}
test_t print_transcations()
{
	Print_transaction_Data();
	return PASS;
}
int main(void) {
	//test case 1
	/*if(Approve_test()==PASS)
	{
		printf("PASS\n");
		fflush(stdin);fflush(stdout);
	}
	else
	{
		printf("Failed\n");
		fflush(stdin);fflush(stdout);
	}*/
	/*//test case 2
		if(Declined_test_expired_card()==PASS)
		{
			printf("PASS\n");
			fflush(stdin);fflush(stdout);
		}
		else
		{
			printf("Failed\n");
			fflush(stdin);fflush(stdout);
		}*/
	/*//test case 3
			if(Declined_test_noEnough_Balance()==PASS)
			{
				printf("PASS\n");
				fflush(stdin);fflush(stdout);
			}
			else
			{
				printf("Failed\n");
				fflush(stdin);fflush(stdout);
			}*/
	/*//test case 4
				if(Declined_test_Fack_ACC_number()==PASS)
				{
					printf("PASS\n");
					fflush(stdin);fflush(stdout);
				}
				else
				{
					printf("Failed\n");
					fflush(stdin);fflush(stdout);
				}*/


	//test case 5
					if(Declined_test_exceedMax_amount()==PASS)
					{
						printf("PASS\n");
						fflush(stdin);fflush(stdout);
					}
					else
					{
						printf("Failed\n");
						fflush(stdin);fflush(stdout);
					}

	//test case 6
					if(print_transcations()==PASS)
										{
											printf("PASS\n");
											fflush(stdin);fflush(stdout);
										}
										else
										{
											printf("Failed\n");
											fflush(stdin);fflush(stdout);
										}
}
