/*
 * APP.h
 *
 * Created: 8/4/2021 3:33:30 PM
 *  Author: Shady Mamdouh
 */ 


#ifndef APP_H_
#define APP_H_

#define TEMPSENSOR_CH 0UL
#define TEPSENSOR_VREF 5UL

/***************nsertion states**************************/
typedef enum insertionState_t
{
	Inserted,
	not_inserted
}insertionState_t;



/**************************************************************/
/***************initialization states**************************/
#define NOT_Initialized 0
#define Initialized 1


/**************************************************************/
#define ADMIN_MODE 0
#define USER_MODE 1

/************************************************************/
typedef enum ATM_ERRORS_t
{
	ERROR,
	NO_ERROR
	
}ATM_ERRORS_t;

/************************************************************/
typedef enum enCompareCommand_t
{
	EQUAL,
	NOT_EQUAL
}enCompareCommand_t;

/*****************************************************************************/
enCompareCommand_t APP_CommandCompare(void);
void APP_APPToTerminalResponse(uint8_t *pString);
uint8_t APP_ReceiveFromTerminal(void);
ATM_ERRORS_t APP_Init(void);
ATM_ERRORS_t APP_GetCardData(void);
ATM_ERRORS_t APP_ExtractDataFromFrame(void);
ATM_ERRORS_t APP_responseToCardInsertion(void);
void APP_Delay_ms(uint32_t u32_Timemsec);
void APP_UartAdminCommandHandler(void);
ATM_ERRORS_t APP_AdminModeHandler(void);
ATM_ERRORS_t APP_ReceiveBalance(void);
ATM_ERRORS_t APP_receivePAN(void);
uint16_t APP_NumberofStoredCustomers(void);
uint16_t APP_CustomerMemlocstart(uint16_t u16_CustomersNumber);
uint8_t APP_StoreCustomerDataEEPROM(void);
void APP_DisplayTotNumOfCustomers(void);
void APP_ClearTotalNumberOfCustomers(void);
ATM_ERRORS_t APP_UpdateMaxAmount(void);
uint8_t APP_ReadCustomerDataByID(uint16_t u16_CustomerID);
uint8_t APP_checkPan(void);
uint8_t APP_SearchCustomerByPAN(void);
ATM_ERRORS_t APP_getPasswordFromUser(void);
ATM_ERRORS_t APP_CheckPasswordOfUser(void);
ATM_ERRORS_t APP_userPassHandler(void);
void APP_floatTostringconvert(float fLoatAmount, uint8_t *string);
float APP_stringToFloat(uint8_t *string,uint8_t u8size);
uint32_t APP_CalPower(uint8_t base , uint8_t power);
ATM_ERRORS_t DiplayAmountLCD(void);
ATM_ERRORS_t APP_GetUserAmount(void);
ATM_ERRORS_t APP_GetMaxAmountFromDB(void);
ATM_ERRORS_t APP_checkMaxamount(void);
ATM_ERRORS_t APP_checkBalance(void);
uint16_t APP_GetCustomerID(void);
ATM_ERRORS_t APP_ApproveTransaction(void);
void DisplayNewBalanceLCD(void);
ATM_ERRORS_t APP_TemperatureCheck(void);
void EXTI0_Handler(void);
uint8_t APP_GetTemperature(void);
ATM_ERRORS_t APP_GetState(void);
ATM_ERRORS_t APP_UpdateState(void);
uint8_t APP_AdminCheckPassword(void);
uint8_t APP_DisplayCustomerDatafromBuffer(void);
uint8_t APP_displayAllCustomer(void);
void APP_ClearTotalNumberOfCustomers(void);
uint8_t APP_ATMStatuscheck(void);
#endif /* APP_H_ */