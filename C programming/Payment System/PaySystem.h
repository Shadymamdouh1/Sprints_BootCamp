/*
 * PaySystem.h
 *
 *  Created on: Jul 12, 2021
 *      Author: HP
 */

#ifndef PAYSYSTEM_H_
#define PAYSYSTEM_H_

//Card Data
typedef struct ST_cardData_t
{
 uint8_t CardHolderName[25];
 uint8_t PrimaryAccountNumber[20];
 uint8_t CardExpirationDate[6];
} ST_cardData_t;

//terminal Data
typedef struct ST_TerminalData_t
{
	float transAmount;
	float MaxtransAmount;
	uint8_t TransactionDate[11];
} ST_TerminalData_t;

//transaction state
typedef enum EN_TransState_t
{
	DECLINED,
	APPROVED
}EN_TransState_t;


//transaction Data
typedef struct ST_Transaction_t
{
	ST_cardData_t CardHolderData;
	ST_TerminalData_t TransData;
	EN_TransState_t TransStat;

}ST_Transaction_t;
//Server Data
typedef struct ST_accountBalance_t
{
	uint8_t PrimaryAccountNumber[20];
	float Balance;

} ST_accountBalance_t;




//APIs
uint8_t GetCardData(ST_cardData_t *Data);
EN_TransState_t GetTerminalData(ST_TerminalData_t *TerData,ST_cardData_t *CardData);
EN_TransState_t Server_check(ST_TerminalData_t *TerData,ST_cardData_t *CardData);
void Save_Transaction_Data(ST_TerminalData_t *TerData,ST_cardData_t *CardData,EN_TransState_t status);
void Print_transaction_Data(void);
#endif /* PAYSYSTEM_H_ */
