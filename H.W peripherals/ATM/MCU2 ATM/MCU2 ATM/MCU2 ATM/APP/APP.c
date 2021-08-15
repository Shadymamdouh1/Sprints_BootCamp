/*
 * APP.c
 *
 * Created: 8/4/2021 3:33:17 PM
 *  Author: Shady Mamdouh
 */ 
/***********************INCLUDES*****************************/
#include "types.h"
#include "..\ECUAL\EEPROM\EEPROM.h"
#include "..\ECUAL\KEYPAD\keypad.h"
#include "..\ECUAL\LCD\LCD.h"
#include "..\ECUAL\EEPROM\EEPROM.h"
#include "..\MCAL\TIMER\timer.h"
#include "..\MCAL\TIMER\timer_Cfg.h"
#include "..\MCAL\SPI\spi.h"
#include "..\MCAL\SPI\spiConfig.h"
#include "..\MCAL\UART\uart.h"
#include "..\MCAL\UART\uartConfig.h"
#include "..\ECUAL\MOTORS\Motors.h"
#include "..\ECUAL\TEMPSENSOR\TempSensor.h"
#include "..\MCAL\INTERRUPTS\Interrupts.h"
#include "APP.h"

/************************MACORS****************************/
#define CARD_BUFFER_SIZE 28UL
#define PAN_BUFFER_SIZE  10UL
#define PIN_BUFFER_SIZE  5UL
#define NAME_BUFFER_SIZE 10UL
#define MAX_NUMBER_CUSTOMERS 1500UL
#define CustomerDataBuffersize 19UL
/**********************BUFFERS***************************/
/* CARD Data buffer */
uint8_t CardReceivedBuffer[CARD_BUFFER_SIZE];
/* Password buffer Entered by user  */
uint8_t UserPass[4];
/* PAN Buffer */
uint8_t PAN_buffer[PAN_BUFFER_SIZE];
/* PIN Buffer */
uint8_t PIN_buffer[PIN_BUFFER_SIZE];
/* Name Buffer */
uint8_t Name_buffer[NAME_BUFFER_SIZE];
/* command buffer */
uint8_t Command[6];
/* Data buffer for receiving Data from the the terminal */
uint8_t TerminalBuffer[20];
/* buffer will hold amount*/
uint8_t AmountBuffer[8];
uint8_t MAXamountBuffer[8];
uint8_t BalanceBuffer[8];
/* Admin Command */
uint8_t AdminCommand[]="ADMIN";
uint8_t AdminPassword[]="2307";
/* customer Data buffer */
/* first 2 locations is Customer ID then 9 for PAN and 8 for balance total 19*/
uint8_t CustomerData[CustomerDataBuffersize];

/******************Global variables & states holders*****************************/
/* UART interrupt counter for receive command */
uint8_t gu8_counter=0;
/* UART interrupt pointer for receive data */
uint8_t *pu8_uartReceiveData;
/* Max amount is initialized or not */
uint8_t u8_MaxamountState ;
/* card state */
uint8_t CardState =NOT_Initialized;
/* card inserted state */
 volatile uint8_t CardinsertionState =not_inserted;
/* ATM State*/
uint8_t ATM_State ;
/* ATM MODE */
uint8_t ATM_mode =	ADMIN_MODE;
/* for balance and amount check */
float fBalance;
float fAmount ;
/*******************************************************************************/
ATM_ERRORS_t APP_Init(void)
{
	GptInit();
	USART_Init();
	MCAL_SpiInit();
	LCD_init();
	keyPad_init();
	ECUAL_EEPROMInit();
	MOTOR_Init();
	EXTI0_init(Failing);
	/* set EXTI0 call back function */
	SetEXTI0CallBackFunction(EXTI0_Handler);
	                 /*PORTA P0     5V at AVCC */
	TempSensorInit(TEMPSENSOR_CH,TEPSENSOR_VREF);
	/* initialize the UART to receive Command using interrupts */
	USART_Receive_INTDriven(pu8_uartReceiveData,APP_UartAdminCommandHandler);
	if (APP_ATMStatuscheck()==ERROR)
	{
		APP_APPToTerminalResponse("MAX Amount is not initialized \r");
	}
	else
	{
		ATM_mode =USER_MODE;
	}
	
}
void EXTI0_Handler(void)
{ 
	/* update the card insertion state */
	CardinsertionState =Inserted;
	/* move the card motor towards the ATM */
	CardMotorRight();
	/* disable interrupt */
	EXTI0_Disable();
	
}
uint8_t APP_GetTemperature(void)
{
	uint8_t u8_Temp;
	TempSensorGetTemp(&u8_Temp);
	return u8_Temp;
}


ATM_ERRORS_t APP_GetState(void)
{
	if (APP_ATMStatuscheck()==NO_ERROR)
	{
		ATM_mode=USER_MODE;
	}
	uint8_t u8_KEY;
	if (ATM_mode==USER_MODE)
	{
		LCD_clear_screen();
		
		LCD_display_String("1-Insert Card");
		LCD_GoTo_xy(1,0);
		LCD_display_String("2-Temperature");
		
		while(1)
		{
			
			u8_KEY =keyPad_GetKey();
			if (u8_KEY=='1')
			{
				/* Enable INT0 */
				EXTI0_Enable();
				LCD_clear_screen();
				LCD_display_String("Insert The Card");
				/* wait till card insertion */
				
				while(CardinsertionState !=Inserted);
				break;
			}
			else if (u8_KEY=='2')
			{
				/* display temp */
				LCD_clear_screen();
				LCD_display_String("Temperature is :");
				LCD_GoTo_xy(1,0);
				LCD_DisplayInteger(APP_GetTemperature())  ;
				APP_Delay_ms(2000);
				break;
			}
			else
			{
				continue;
			}
	}
}
}


ATM_ERRORS_t APP_UpdateState(void)
{
	if (CardinsertionState== Inserted)
	{
		/*TEST */
		LCD_clear_screen();
		APP_GetCardData();
		APP_ExtractDataFromFrame();
		APP_responseToCardInsertion();
	}
	
}

void APP_UartAdminCommandHandler(void)
{
	
	
	if (*pu8_uartReceiveData=='\r' || gu8_counter==5)
	{
		Command[gu8_counter]='\r';
		/* compare the command*/
		if (APP_CommandCompare()==EQUAL)
		{
			ATM_mode = ADMIN_MODE;
			APP_AdminModeHandler();
		}
		
		
		/* clear buffers and vars */
		gu8_counter =0;
		uint8_t u8_I;
		for(u8_I=0;u8_I<6;u8_I++)
		{
			Command[u8_I]=0;
		}
		
	}
	/* receive data into command buffer */
	else
	{
		Command[gu8_counter]=*pu8_uartReceiveData;
		gu8_counter++;
	}
	
	/* update the ATM to user mode */
	ATM_mode =USER_MODE;
}

enCompareCommand_t APP_CommandCompare(void)
 {
	 uint8_t u8_counter=0;
	 while(AdminCommand[u8_counter] !=  '\0' && Command[u8_counter] != '\r')
	 {
		 if (AdminCommand[u8_counter]==Command[u8_counter])
		 {
			 u8_counter++;
			 continue;
		 }
		 else
		 {
			 return NOT_EQUAL;
		 }
	 }
	 return EQUAL;
 }

/* delay function in msec */
void APP_Delay_ms(uint32_t u32_Timemsec)
{
	uint32_t u32_counter =0;
	for (u32_counter=0;u32_counter<u32_Timemsec;u32_counter++)
	{  
		/* this function takes timer id and number of ticks so if fck 1mega */
		/* the timer time base will be  1micro so we pass 1000 micro to represent 1 msec*/ 
		GptStart_Sync(0,1000);
	}
}

/* Send Message to the terminal */
void APP_APPToTerminalResponse(uint8_t *pString)
{
	/* Disable UART RXC interrupts */
	USART_RxInterruptDiable();
	
	while(*pString !='\0')
	{
		USART_Transmit(*pString);
		pString++;
	}
	/* Enable UART RXC  interrupts */
	USART_RxInterruptEnable();
}

ATM_ERRORS_t APP_GetCardData(void)
{
	
	/* counter */
	uint8_t u8counter =0;
	
	
	/* receive Data from the Card */
	uint8_t u8_received=0;	
	/* receive the Card Data frame that contains PAN & PIN & Card holder name */
	
	for(u8counter=0;u8counter<CARD_BUFFER_SIZE;u8counter++)
	{
	MCAL_SPIMasterReceive(&CardReceivedBuffer[u8counter]);
	
	}	
		
}

ATM_ERRORS_t APP_ExtractDataFromFrame(void)
{
	uint8_t u8_counter1=0;
	uint8_t u8_counter2=0;
	/* extract the Card state */
	if (CardReceivedBuffer[1]==55)
	{
		CardState = Initialized;
	}
	else
	{
		CardState =NOT_Initialized;
	}
	
	/* Extract Card Holder Name */
	u8_counter2 =0;
	/* Name Data starts from the index 2 and end at index 11 in the frame */
	for (u8_counter1=2;u8_counter1<=11;u8_counter1++)
	{
		 Name_buffer[u8_counter2] = CardReceivedBuffer[u8_counter1];
		 u8_counter2++;
		
	}
	/* Extract the PAN from the frame */
	/*PAN Data starts from the index 12 and end at index 21 in the frame */
	u8_counter2 =0;
	for (u8_counter1=12;u8_counter1<=21;u8_counter1++)
	{
		PAN_buffer[u8_counter2] = CardReceivedBuffer[u8_counter1];
		u8_counter2++;
		
	}
	/* Extract the PIN from the frame */
	/*PAN Data starts from the index 12 and end at index 21 in the frame */
	u8_counter2 =0;
	for (u8_counter1=22;u8_counter1<=25;u8_counter1++)
	{
		PIN_buffer[u8_counter2] = CardReceivedBuffer[u8_counter1];
		u8_counter2++;
		
	}
	/* inset \0 at the end of the PIN */
	PIN_buffer[4]='\0';
	
}

ATM_ERRORS_t APP_getPasswordFromUser(void)
{
	uint8_t u8_key;
	uint8_t u8counter=0;
	while(1)
	{
		u8_key=keyPad_GetKey();
		/* nothing is pressed */
		if(u8_key =='A')
		{
			continue;
		}
		else
		{
			UserPass[u8counter]= u8_key;
			LCD_display_charcter('*');
			u8counter++;
			
	}
	
	if (u8counter==4)
	{
		break;
	}	
		
}
	
	
}

ATM_ERRORS_t APP_CheckPasswordOfUser(void)
{
	uint8_t u8_counter=0;
	uint8_t u8_flag=0;
	for(u8_counter=0;u8_counter<4;u8_counter++)
	{
		if (PIN_buffer[u8_counter]==UserPass[u8_counter])
		{
			continue;
		}
		else
		{
			u8_flag=1;
			break;
		}
	}
	/* wrong pass */
	if (u8_flag==1)
	{
		return ERROR;
	}
	else
	{
		return NO_ERROR;
	}
}

ATM_ERRORS_t DiplayAmountLCD(void)
{
	uint8_t u8_counter =0;
	for (u8_counter=0;u8_counter<8;u8_counter++)
	{
		LCD_display_charcter(AmountBuffer[u8_counter]);
	}
	
}

ATM_ERRORS_t APP_GetUserAmount(void)
{
	uint8_t u8_counter =0;
	uint8_t u8_flag =0;
	/* display amount format xxxxx.xx */
	for (u8_counter=0;u8_counter<8;u8_counter++)
	{
		if (u8_counter==5)
		{
		 AmountBuffer[u8_counter]= '.';
		 continue;	
		}
		AmountBuffer[u8_counter]='x';
	}
	LCD_clear_screen();
	LCD_display_String("Enter amount :");
	LCD_GoTo_xy(1,0);
	DiplayAmountLCD();
	uint8_t u8_key;
	u8_counter=0;
	
	while(1)
	{
		
		
		
		
		u8_key=keyPad_GetKey();
		
		
		/* nothing is pressed */
		if(u8_key =='A')
		{
			
			continue;
		}
		else
		{
			if (u8_counter ==5)
			{
				AmountBuffer[u8_counter] ='.';
				u8_counter++;
				AmountBuffer[u8_counter]= u8_key;
				LCD_GoTo_xy(1,0);
				DiplayAmountLCD();
				u8_counter++;
				continue;
			}
			else
			{
				AmountBuffer[u8_counter]= u8_key;
				LCD_GoTo_xy(1,0);
				DiplayAmountLCD();
				u8_counter++;
			}
			
			
		}
		
		if (u8_counter==8)
		{
			u8_counter=0;
			for(u8_counter=0;u8_counter<8;u8_counter++)
			{   
				/* the dot */
				if (u8_counter ==5)
				{
					continue;
				}
				/* check entering non numeric values */
				if (AmountBuffer[u8_counter] >57 || AmountBuffer[u8_counter] < 48 )
				{
					u8_flag =1;
					break;
				}
				
				
			}
			
			if (u8_flag==1)
			{
				return ERROR;
			}
			else
			{
				return NO_ERROR;
			}
			
		}
	
	}
	
	
}

void APP_floatTostringconvert(float fLoatAmount, uint8_t *string)
{
	/* integer part */
	int integerPart ;
	/* fraction part */
	float fractionPart;
	/* fraction part to integer */
	int Fint ;
	
	integerPart = (int)fLoatAmount;
	fractionPart = fLoatAmount - integerPart;
	/* take 2 numbers after dot */ //ex .25 will be 25
	Fint =(int) (fractionPart*100.0);
	
	int u8_counter =4;
	
	string[7]= (Fint%10)+48;
	string[6]= (Fint/10)+48;
	string[5]='.';
	for(u8_counter=4;u8_counter>=0;u8_counter--)
	{
		string[u8_counter] =(integerPart %10)+48;
		integerPart =(integerPart/10);
	}
	
	
}

uint32_t APP_CalPower(uint8_t base , uint8_t power)
{
	uint8_t u8_counter=0;
	uint32_t u32_result=1;
	if (power ==0)
	{
		return 1;
	}
	else
	{
		for(u8_counter=1;u8_counter<=power;u8_counter++)
		{
			u32_result =u32_result * base;
		}
	}
	return u32_result;
}

float APP_stringToFloat(uint8_t *string,uint8_t u8size)
{
	float fvalue;
	float fractionPart;
	uint8_t u8_counter =0;
	uint32_t integerPart=0 ;
	uint8_t intPartSize = u8size -3 ;  // in our case 5 
	for(u8_counter=0;u8_counter<5;u8_counter++)
	{
		integerPart =integerPart +( (string[u8_counter]-48)*(APP_CalPower(10,(intPartSize-u8_counter-1)))  ) ;
	}
	fractionPart =( ((string[6]-48)*10) +(string[7]-48) ) /100.0;
	
	fvalue = integerPart + fractionPart;
	
	return fvalue;
	
	
}

ATM_ERRORS_t APP_userPassHandler(void)
{
	uint8_t u8_Counter=0;
	uint8_t u8_flag =0;
	
	
	
	/* 3 Trial entering wrong password */
	
	for(u8_Counter=0;u8_Counter<3;u8_Counter++)
	{
		LCD_clear_screen();
		LCD_display_String("Enter Password :");
		LCD_GoTo_xy(1,0);
		APP_getPasswordFromUser();
		
		if (APP_CheckPasswordOfUser()==NO_ERROR)
		{
			/* correct password */
			
			u8_flag=1;
			break;
			
		}
		LCD_clear_screen();
		LCD_display_String("Wrong password");
		LCD_GoTo_xy(1,0);
		LCD_display_String("remaining try:");
		LCD_DisplayInteger(3-u8_Counter-1);
		APP_Delay_ms(1000);
		
	}
	if (u8_flag==1)
	{
		LCD_clear_screen();
		LCD_display_String("Correct password");
		APP_Delay_ms(1000);
		return NO_ERROR;
	}
	else
	{
		return ERROR ;
		 /* 3 trial wrong pass */
		
	}
}

ATM_ERRORS_t APP_GetMaxAmountFromDB(void)
{
	uint8_t u8_counter =0;
	uint16_t StartAdd = 2; // max amount starts from add 2 in DB
	for (u8_counter=0;u8_counter<8;u8_counter++)
	{
		APP_Delay_ms(20);
		ECUAL_EEPROMRead(StartAdd,&MAXamountBuffer[u8_counter]);
		StartAdd++;
	}
	
}

ATM_ERRORS_t APP_checkMaxamount(void)
{
	float fuserAmount ;
	float fMaxAmount ;
	
	/* get max amount from Data base */
	APP_GetMaxAmountFromDB();
	
	 fuserAmount = APP_stringToFloat(AmountBuffer,8);
	 fMaxAmount =  APP_stringToFloat(MAXamountBuffer,8);
	 
	 /* the amount exceeds the max amount */
	 if (fMaxAmount<fuserAmount)
	 {
		 return ERROR ;
	 }
	 else
	 {
		 return NO_ERROR;
	 }
	 
	
}

ATM_ERRORS_t APP_checkBalance(void)
{
	uint8_t u8_counter =0;
	
	/* Get Balance from the Customer Data Buffer */
	for(u8_counter=0;u8_counter<8;u8_counter++)
	{       
		/* Balance starts from index 11 in the customer buffer */
		BalanceBuffer[u8_counter]= CustomerData[u8_counter+11];
	}
	 /* convert strings to float numbers */
	fBalance =APP_stringToFloat(BalanceBuffer,8);
	fAmount = APP_stringToFloat(AmountBuffer,8);
	
	/* check the balance */
	if (fBalance > fAmount)
	{
		return NO_ERROR;
	}
	else
	{
		return ERROR;
	}
}

uint16_t APP_GetCustomerID(void)
{
	uint16_t u16_CustomerID ;
	u16_CustomerID =(uint8_t)(CustomerData[0]);
	u16_CustomerID |=((CustomerData[1])<<8);
	return u16_CustomerID;
}

void DisplayNewBalanceLCD(void)
{ 
	uint8_t u8_counter ;
	LCD_clear_screen();
	LCD_display_String("The New Balance is:");
	for(u8_counter=0;u8_counter<8;u8_counter++)
	{
		LCD_display_charcter(BalanceBuffer[u8_counter]);
	}
	APP_Delay_ms(2000);
}

ATM_ERRORS_t APP_ApproveTransaction(void)
{

	uint8_t u8_counter =0;
	uint16_t u16_CustomerID ;
	/* subtract the amount from the balance */
	fBalance = fBalance -fAmount ;
	/* convert the new balance to string format */
	 APP_floatTostringconvert(fBalance,BalanceBuffer);
	 
	 /* store the Customer Balance buffer for the current customer ID */
	 
	    /* Get the customer ID  */
	   u16_CustomerID = APP_GetCustomerID();
	 /* calculate start Address */
	 /* 2 bytes for total num of customer + 8 for max amount + 11 from start of customer data to start of his balance */
	 uint16_t u16_StratAdress ;     
	 u16_StratAdress = (((u16_CustomerID -1)*CustomerDataBuffersize)+21);
	 /* store the new balance */
	 for(u8_counter=0;u8_counter<8;u8_counter++)
	 {
		 APP_Delay_ms(20);
		 ECUAL_EEPROMWrite(u16_StratAdress,BalanceBuffer[u8_counter]);
		 u16_StratAdress++;
	 }
	 
	 return NO_ERROR;
}


ATM_ERRORS_t APP_responseToCardInsertion(void)
{
	uint8_t u8_KEY;
	/* check the Card State */
	if (CardState==Initialized)
	{
		LCD_clear_screen();
		LCD_display_String("   waiting....    ");
		LCD_clear_screen();
		
		
		
		if (APP_userPassHandler()==NO_ERROR)
		{
			/*hello message with card holder name */
			LCD_clear_screen();
			LCD_display_String("      Hello    ");
			LCD_GoTo_xy(1,0);
			LCD_display_String(Name_buffer);
			/*****************************/
			APP_Delay_ms(2000);
			/****************************/
			
			if (APP_GetUserAmount()==ERROR)
			{
				
					LCD_clear_screen();
					LCD_display_String("wrong format");
			}
			else
			{
				
				LCD_clear_screen();
				LCD_display_String("waiting");
				if(APP_SearchCustomerByPAN()==NO_ERROR)
				{
					
					if (APP_checkMaxamount()==NO_ERROR)
					{  
						
						if (APP_checkBalance()==NO_ERROR)
						{
							
							/* wait user confirmation */
							LCD_clear_screen();
							LCD_display_String("1-Confirm");
							LCD_GoTo_xy(1,0);
							LCD_display_String("2-Cancel");
							
							while(1)
							{
								
								
								
								
								u8_KEY =keyPad_GetKey();
								if (u8_KEY=='1')
								{
									/* approve the transaction */
									/* this is a critical part so we will disable ADMIN UART Interrupt */
									USART_RxInterruptDiable();
									
									if (APP_ApproveTransaction()==NO_ERROR)
									{
										LCD_clear_screen();
										LCD_display_String("the transaction  is approved");
										APP_Delay_ms(2000);
										LCD_clear_screen();
										DisplayNewBalanceLCD();
										APP_Delay_ms(2000);
										LCD_clear_screen();
										LCD_display_String("Take your money");
										APP_Delay_ms(2000);
										/* Money Motor On */
										MoneyMotorON();
										LCD_clear_screen();
										LCD_display_String("Take your Card");
										/* card motor Kick out the card to left */
										CardMotorLeft();
										APP_Delay_ms(2000);
										
										LCD_clear_screen();
										LCD_display_String("Thank you");
										APP_Delay_ms(2000);
										LCD_clear_screen();
										/* update card insertion state to not inserted */
										CardinsertionState =not_inserted;
										/* enable the interrupt again */
										USART_RxInterruptEnable();
										break;
									}
									
									
								}
								else if (u8_KEY=='2')
								{
									/* cancel transaction */
									LCD_clear_screen();
									LCD_display_String("Canceled");
									APP_Delay_ms(2000);
									LCD_clear_screen();
									LCD_display_String("Take your Card");
									/* card motor Kick out the card to left */
									CardMotorLeft();
									APP_Delay_ms(2000);
									LCD_clear_screen();
									LCD_display_String("Thank you");
									APP_Delay_ms(2000);
									LCD_clear_screen();
									/* update card insertion state to not inserted */
									CardinsertionState =not_inserted;
									break;
								}
								else
								{
									continue;
								}
							}
							
						}
						else{
							/* insufficient fund */
							LCD_clear_screen();
							LCD_display_String("insufficient  fund");
							APP_Delay_ms(2000);
							LCD_clear_screen();
							LCD_display_String("Take your Card");
							/* card motor Kick out the card to left */
							CardMotorLeft();
							APP_Delay_ms(2000);
							LCD_clear_screen();
							LCD_display_String("Thank you");
							APP_Delay_ms(2000);
							LCD_clear_screen();
							/* update card insertion state to not inserted */
							CardinsertionState =not_inserted;
						}
						
					}
					else
					{
						/* exceed max amount */
						LCD_clear_screen();
						LCD_display_String("exceeds maximum amount");
						APP_Delay_ms(2000);
						LCD_clear_screen();
						LCD_display_String("Take your Card");
						/* card motor Kick out the card to left */
						CardMotorLeft();
						APP_Delay_ms(2000);
						LCD_clear_screen();
						LCD_display_String("Thank you");
						APP_Delay_ms(2000);
						LCD_clear_screen();
						/* update card insertion state to not inserted */
						CardinsertionState =not_inserted;
					}
					{
						
					}
					
				}
				else
				{  /* the PAN number is not exist in DB */
					/* the Card is blocked */
					LCD_clear_screen();
					LCD_display_String("PAN number is   founded in DB");
					LCD_clear_screen();
					LCD_display_String("The Card        is blocked ");
					CardMotorRight();
					APP_Delay_ms(2000);
					LCD_clear_screen();
					LCD_display_String("please contact service provider");
					APP_Delay_ms(2000);
					/* update card insertion state to not inserted */
					CardinsertionState =not_inserted;
					
				}
			}
			
			
		}
		/* the user entered 3 wrong passwords */
	   else
	   {  
		   /* Card is Blocked */
		   /* move Card motor to right toward the ATM */
		   CardMotorRight();
		   LCD_clear_screen();
		   LCD_display_String("you entered 3   wrong passwords");
		   APP_Delay_ms(2000);
		   LCD_clear_screen();
		   LCD_display_String("The card        Is blocked");
		   APP_Delay_ms(2000);
		   LCD_clear_screen();
		   LCD_display_String("please contact service provider");
		   APP_Delay_ms(2000);
		   /* update card insertion state to not inserted */
		   CardinsertionState =not_inserted;
		   return ERROR;
		  
		   
	   }
	
	}
	else
	{ // card not initialized */
		
		LCD_clear_screen();
		LCD_display_String("The Card is not initialized");
		APP_Delay_ms(2000);
		/* BLOCK THE card */
		CardMotorRight();
		LCD_clear_screen();
		LCD_display_String("The Card has     been blocked ");
		APP_Delay_ms(2000);
		LCD_clear_screen();
		LCD_display_String("Please contact  service provider");
		APP_Delay_ms(2000);
		CardinsertionState =not_inserted;
	}
}

/* Receive Message From the terminal */
 uint8_t APP_ReceiveFromTerminal(void)
{
	
	 
	/* counter */
	uint8_t u8_counter = 0;
	/* string size */
	uint8_t u8_STRSize=0;
	/* start receiving */
	USART_Receive(&TerminalBuffer[u8_counter]);
	
	/* check ENTER Key is pressed that is an indicator to the end of string */
	while(TerminalBuffer[u8_counter] != '\r')
	{
		u8_counter++;
		USART_Receive(&TerminalBuffer[u8_counter]);
	}
	/* ENTER key is pressed in the terminal */
	if (TerminalBuffer[u8_counter] == '\r')
	{
		/* close the string by adding null indicator */
		
		TerminalBuffer[u8_counter] = '\0';
	}
	u8_STRSize =(u8_counter+1);
	/* return string size */
	return u8_STRSize ;
}


ATM_ERRORS_t APP_ReceiveBalance(void)
{
	uint8_t u8_counter=0;
	uint8_t u8_SIZE =0;
	uint8_t u8_flag =0;
	while(1)
	{
		u8_flag=0;
		
		APP_APPToTerminalResponse("please Enter Customer Balance in format xxxxx.xx\r");
		u8_SIZE=APP_ReceiveFromTerminal();
		if (u8_SIZE >9 || u8_SIZE< 9)
		{
			APP_APPToTerminalResponse("Invalid Balance Formate ,Balance must be in format xxxxx.xx\r");
			u8_flag =1;
			continue;
		}
		/* check that Balance contains only numbers except the dot sign in the index 5 */
		for (u8_counter=0;u8_counter<8;u8_counter++)
		{
			/* check the dot */
			if (u8_counter==5)
			{
				if (TerminalBuffer[u8_counter]=='.')
				{
					continue;
				}
				else{
						APP_APPToTerminalResponse("Invalid Balance Formate ,Balance must be in format xxxxx.xx\r");
						u8_flag =1;
						break;
				    }
			}
			/* check if the Balance within numeric characters range or not */
			if (TerminalBuffer[u8_counter] >57 || TerminalBuffer[u8_counter] < 48 )
			{
				APP_APPToTerminalResponse("Invalid Balance Formate , Balance must not contain any characters\r");
				u8_flag =1;
				break;
			}
			else
			{
				continue;
			}
			
		}
			
		if (u8_flag==1)
		{
			continue;
		}
		else if (u8_flag==0)
		{
			/* store to data buffer */
			for(u8_counter=0;u8_counter<8;u8_counter++)
			{
				/* Balance starts at index 10 to index 18 in the CustomerData buffer */
				CustomerData[u8_counter+11] = TerminalBuffer[u8_counter];
			}
			return NO_ERROR;
		}
		
		
		
	}
	
}

ATM_ERRORS_t APP_UpdateMaxAmount(void)
{
	uint8_t u8_counter=0;
	uint8_t u8_SIZE =0;
	uint8_t u8_flag =0;
	while(1)
	{
		u8_flag=0;
		
		APP_APPToTerminalResponse("please Enter Max amount in format xxxxx.xx\r");
		u8_SIZE=APP_ReceiveFromTerminal();
		if (u8_SIZE >9 || u8_SIZE< 9)
		{
			APP_APPToTerminalResponse("Invalid amount Formate ,amount must be in format xxxxx.xx\r");
			u8_flag =1;
			continue;
		}
		/* check that amount contains only numbers except the dot sign in the index 5 */
		for (u8_counter=0;u8_counter<8;u8_counter++)
		{
			/* check the dot */
			if (u8_counter==5)
			{
				if (TerminalBuffer[u8_counter]=='.')
				{
					continue;
				}
				else{
					APP_APPToTerminalResponse("Invalid amount Formate ,amount must be in format xxxxx.xx\r");
					u8_flag =1;
					break;
				}
			}
			/* check if the amount within numeric characters range or not */
			if (TerminalBuffer[u8_counter] >57 || TerminalBuffer[u8_counter] < 48 )
			{
				APP_APPToTerminalResponse("Invalid amount Formate , amount must not contain any characters\r");
				u8_flag =1;
				break;
			}
			else
			{
				continue;
			}
			
		}
		
		if (u8_flag==1)
		{
			continue;
		}
		else if (u8_flag==0)
		{
			uint16_t u16_address=2;
			/* store to data buffer */
			for(u8_counter=0;u8_counter<8;u8_counter++)
			{
				/* Max amount will be stored from the address 0x0002 to 0x0009 */
				ECUAL_EEPROMWrite(u16_address,TerminalBuffer[u8_counter]);
				u16_address++;
				APP_Delay_ms(50);
				
				
			}
			return NO_ERROR;
		}
		
		
		
	}
}

ATM_ERRORS_t APP_receivePAN(void)
{
	uint8_t u8_counter=0;
	uint8_t u8_SIZE =0;
	uint8_t u8_flag =0;
	while(1)
	{
		u8_flag=0;
	
	APP_APPToTerminalResponse("please Enter Customer PAN Number\r");
	
	  u8_SIZE=APP_ReceiveFromTerminal();
	  if (u8_SIZE >10 || u8_SIZE< 10)
	  {
		  APP_APPToTerminalResponse("Invalid PAN Formate , PAN must be 9 numbers\r");
		  u8_flag =1;
	  }
	  /* check that PAN contains only numbers */
	  for (u8_counter=0;u8_counter<9;u8_counter++)
	  {
		   /* check if the PAN within numeric characters or not */
		   if (TerminalBuffer[u8_counter] >57 || TerminalBuffer[u8_counter] < 48 )
		   {
			   APP_APPToTerminalResponse("Invalid PAN Formate , PAN must not contain any characters\r");
			   u8_flag =1;
			   break;
		   }
		   else
		   {
			   continue;
		   }
		  
	  }
	  
	  if (u8_flag==1)
	  {
		  continue;
	  }
	  else if (u8_flag==0)
	  {
		  /* store to data buffer */
		  for(u8_counter=0;u8_counter<9;u8_counter++)
		  {   
			  /* PAN starts at index 2 to index 10 in the CustomerData buffer */
			  CustomerData[u8_counter+2] = TerminalBuffer[u8_counter];
		  }
		  return NO_ERROR;
	  }
	 
	  
	  
	}
}


ATM_ERRORS_t APP_AdminModeHandler(void)
{
	
	uint8_t u8_counter =4;
	uint8_t u8_counter2=0;
	/* check admin password */
	
	while(1)
	{
		APP_APPToTerminalResponse("Please Enter Password\r");
		if (APP_AdminCheckPassword()==NO_ERROR)
		{
			break;
		}
		else
		{
			u8_counter--;
			if (u8_counter==1)
			{
				APP_APPToTerminalResponse("you entered 3 wrong passwords\r");
				// wait 10 seconds 
				USART_Transmit(0x0C);
				for(u8_counter2=0;u8_counter2<9;u8_counter2++)
				{
					USART_Transmit(u8_counter2+49);
					APP_Delay_ms(1000);
					USART_Transmit(0x0C);
				}
				APP_APPToTerminalResponse("back to operation Mode if you want ADMIN mode Write ADMIN Command\r");
				LCD_clear_screen();
				
				LCD_display_String("1-Insert Card");
				LCD_GoTo_xy(1,0);
				LCD_display_String("2-Temperature");
				ATM_mode= USER_MODE;
				return ERROR;
				
			}
			APP_APPToTerminalResponse("wrong password\r");
			
		}
		   
		
	}
	/* disable Card insertion interrupt */
	EXTI0_Disable();
	/* display the tha ATM is out of service */
	LCD_clear_screen();
	LCD_display_String("The ATM is      out of service");
	
	uint8_t u8_receivedData;
	uint8_t u8_ReceivedStringSize;
	/* Disable UART RXC interrupts */
	/* Not to Receiving another ADMIN Command */
	USART_RxInterruptDiable();
	
while(1)
{
		
	
	/* Display options */
	APP_APPToTerminalResponse("Please select option :\r");
	APP_APPToTerminalResponse("1- Add Customer Data\r");
	APP_APPToTerminalResponse("2- Setting Max amount\r");
	APP_APPToTerminalResponse("3- Display all customers Data\r");
	APP_APPToTerminalResponse("4-[Be careful] Clear all customers Data\r");
	APP_APPToTerminalResponse("5- Exit\r");
	/* receive option */
	u8_ReceivedStringSize = APP_ReceiveFromTerminal();
	
	
	/* check the option */
	if (u8_ReceivedStringSize>2)
	{
		APP_APPToTerminalResponse("Invalid option\r");
		continue;
	}
	else
	{
		switch(TerminalBuffer[0])
		{
			case '1' :
			{
				if (APP_receivePAN()==NO_ERROR)
				{
					if (APP_ReceiveBalance()==NO_ERROR)
					{
						
						
						/* Store Data into EEPROM */
						/* that means the memory is full */
						uint8_t temp ;
						temp =APP_StoreCustomerDataEEPROM();
						if (temp == ERROR)
						{
							break;
						}
						else
						{
							APP_APPToTerminalResponse("the Customer Data has been added successfully\r");
							/* Display the total number of the customers */
							APP_APPToTerminalResponse("the New total number of customer in Data base :\r");
							APP_DisplayTotNumOfCustomers();
							break;
						}
						break;
					}
			
				}
			}
			case '2' :
			{
				uint8_t temp ;
				temp =APP_UpdateMaxAmount();
				if (temp==NO_ERROR)
				{
					APP_APPToTerminalResponse("The max amount has been initialized successfully\r");
					/* update max amount state */
					break;
				}
				else{
					
						break;
				
				    }
				
			}
			case '3' :
			{
				APP_displayAllCustomer();
				break;
		    }
			case '4' :
			{
				
					APP_ClearTotalNumberOfCustomers();
					APP_APPToTerminalResponse("*******************************************************\r");
					APP_APPToTerminalResponse("      Data have been deleted successfully\r");
					APP_APPToTerminalResponse("********************************************************\r");
				
					break;
				}
		
			case '5' :
			{
				
				// Exit handler
				APP_APPToTerminalResponse("back to operation Mode if you want ADMIN mode Write ADMIN Command\r");
				ATM_mode= USER_MODE;
				
				/* Enable accepting Cards again */
				EXTI0_Enable();
				/* Enable UART RXC  interrupts */
				USART_RxInterruptEnable();
			/*	LCD_clear_screen();
				LCD_display_String("1-Insert Card");
				LCD_GoTo_xy(1,0);
				LCD_display_String("2-Temperature");*/
				return ERROR;
				break;
			}
			default:
			{
				APP_APPToTerminalResponse("Invalid option\r");
			}
				
		}
		
	}
	
}
    /* Enable accepting Cards again */
	 EXTI0_Enable();
	/* Enable UART RXC  interrupts */
	USART_RxInterruptEnable();
}
					


void APP_DisplayTotNumOfCustomers(void)
{  
	uint16_t u16_CustomesNumber;
	uint8_t u8_counter ;
	uint8_t string[5]={0,0,0,0,0};
	string[4]='\r';
	/* to display we have to Convert 2 bytes number to string */
	
	/* first read Total number */
	u16_CustomesNumber = APP_NumberofStoredCustomers();
	if (u16_CustomesNumber==0)
	{
		string[0]='0';
	}
	while(u16_CustomesNumber !=0)
	{
		 /* we add 48 to save at char form */
		string[u8_counter]= ( (u16_CustomesNumber % 10 ) + 48 ) ;
		u16_CustomesNumber = u16_CustomesNumber /10;
		u8_counter--;
	}
	for(u8_counter=0;u8_counter<5;u8_counter++)
	{
		USART_Transmit(string[u8_counter]);
	}
	
}


uint16_t APP_NumberofStoredCustomers(void)
{
	uint16_t u16_CustomersNumber =0;
	uint16_t u6_temp =0;
	/* Read the first 2 locations in the memory that represents the number of customers */
	/* first byte */
	ECUAL_EEPROMRead(0,&u6_temp);
	u16_CustomersNumber=u6_temp;
	APP_Delay_ms(50);
	/*second byte */
	ECUAL_EEPROMRead(1,&u6_temp);
	u16_CustomersNumber |=(u6_temp<<8);
	
	return u16_CustomersNumber;
}
uint16_t APP_CustomerMemlocstart(uint16_t u16_CustomersNumber)
{
	uint16_t u16_StartMemoryloc;
	/* check if the memory is full */
	if (u16_CustomersNumber>=MAX_NUMBER_CUSTOMERS)
	{
		APP_APPToTerminalResponse("Memory is Full\r");
		return ERROR;          // it is a unique return value that will not affect the start loc
		                   // because even if there is no Customer data the start add will be larger than 0
	}
	else
	{    
		/* 2 bytes for Customers Number 8 bytes for max amount =10 and Number of customer by 19 byte per customer data */ 
		u16_StartMemoryloc=((u16_CustomersNumber*CustomerDataBuffersize)+10);
		return u16_StartMemoryloc;
	}
	
}

uint8_t APP_StoreCustomerDataEEPROM(void)
{
	uint8_t u8_counter =0;
	uint16_t u16_CustomersNumber ;
	uint16_t u16_StartLocation ;
	/* Get the total Number of Customers */
	u16_CustomersNumber=APP_NumberofStoredCustomers();
	
	/* Check if Memory is full and if not Get the New Customer Address Location */
	u16_StartLocation =APP_CustomerMemlocstart(u16_CustomersNumber);
	
	/* check if the  Memory is Full */
	if (u16_StartLocation==0)
	{
		return ERROR;
	}
	else
	{
		/* store New customer Data with his ID into EEPROM */
		/* first store ID into the buffer */
		/* increment the customer number that represents the new customer ID */
		u16_CustomersNumber++;
		CustomerData[0]=(uint8_t)u16_CustomersNumber;
		CustomerData[1]=(uint8_t)(u16_CustomersNumber>>8);
		
		/* store the whole customer data block */
		
		for(u8_counter=0;u8_counter<19;u8_counter++)
		{
			/* Delay */
			APP_Delay_ms(30);
			ECUAL_EEPROMWrite(u16_StartLocation,CustomerData[u8_counter]);
			/* increment the address */
			u16_StartLocation++;
		}
		
		
		/* Increment the total number of Customers */
		u16_CustomersNumber =u16_CustomersNumber;
		APP_Delay_ms(30);
		ECUAL_EEPROMWrite(0,((uint8_t)u16_CustomersNumber));
		APP_Delay_ms(30);
		ECUAL_EEPROMWrite(1,((uint8_t)(u16_CustomersNumber>>8)));	
		return NO_ERROR;
	}
	
	
	
	
}

void APP_ClearTotalNumberOfCustomers(void)
{
	ECUAL_EEPROMWrite(0,0);
	APP_Delay_ms(50);
	ECUAL_EEPROMWrite(1,0);
}

uint8_t APP_ReadCustomerDataByID(uint16_t u16_CustomerID)
{
	uint8_t u8_counter;
	/* calculate start Address */
	uint16_t u16_StratAdress ;
	u16_StratAdress = (((u16_CustomerID -1)*CustomerDataBuffersize)+10); 
	
      /* read customer data and save it into customer data buffer */
	  
	  for(u8_counter=0;u8_counter<CustomerDataBuffersize;u8_counter++)
	  {
		ECUAL_EEPROMRead(u16_StratAdress,&CustomerData[u8_counter]) ;
		APP_Delay_ms(20);
		u16_StratAdress++;
	  }
	
}
uint8_t APP_checkPan(void)
{
	uint8_t u8_counter;
	/* we will compare between PAN entered by user and the PAN in the current ID */
	 for(u8_counter=0;u8_counter<9;u8_counter++)
	 {
		                           // PAN is located form the 2 index in the customer buffer */
		 if (PAN_buffer[u8_counter]==CustomerData[u8_counter+2])
		 {
			 continue;
		 }
		 else
		 {
				return ERROR;	
		 }
	 }
	 return NO_ERROR;
}

uint8_t APP_SearchCustomerByPAN(void)
{
	
	uint16_t u16_ToTNumOfCustomers;
	uint16_t u16_counter;
	uint8_t u8_flag=0;
	/* first get total numbers of customers */
	u16_ToTNumOfCustomers =APP_NumberofStoredCustomers();
	
	/* start searching */
	for(u16_counter=1;u16_counter<=u16_ToTNumOfCustomers;u16_counter++)
	{
		/* read Data */
		APP_ReadCustomerDataByID(u16_counter);
		/* check PAN */
		if (APP_checkPan()==NO_ERROR)
		{
			u8_flag=1;
			break;
		}
		
	}
	/* that means the customer is exist and stored data Stored at CustomerData buffer */
	if (u8_flag==1)  
	{
		return NO_ERROR;
	}
	/* that means the customer is not exist into Data Base and the card is fake */
	else
	{         
		return ERROR;
	}
	
	
}

uint8_t APP_AdminCheckPassword(void)
{
	uint8_t u8_counter=0;
	uint8_t u_flag =0;
	APP_ReceiveFromTerminal();
	for(u8_counter=0;u8_counter<4;u8_counter++)
	{
		if(AdminPassword[u8_counter] == TerminalBuffer[u8_counter])
		{
			continue;
		}
		else{
			u_flag =1;
			break;
		    }
		
	}
	if (u_flag==1)
	{
		return ERROR;
	}
	else
	{
		return NO_ERROR;
	}
	 
	
	
	
}

uint8_t APP_DisplayCustomerDatafromBuffer(void)
{
	uint8_t u8_counter =0;
	uint16_t U16_customerID=0;
	uint8_t u8_Temp;
	U16_customerID =APP_GetCustomerID();
	uint8_t IDstring[5]={0,0,0,0,0};
	
	
	if (U16_customerID==0)
	{
		APP_APPToTerminalResponse('0');
		return ERROR;
	}
	u8_counter=3;
	APP_APPToTerminalResponse("*************************************************************\r");
	/* convert the number to string */
	while(u8_counter !=0)
	{
		IDstring[u8_counter] = (U16_customerID %10)+48;
		U16_customerID =U16_customerID/10;
		u8_counter--;
	}
	 IDstring[u8_counter] = (U16_customerID %10)+48;
	
	APP_APPToTerminalResponse("ID : ");
	APP_APPToTerminalResponse(IDstring);
	APP_APPToTerminalResponse("\r");
	
	/* display PAN */
	APP_APPToTerminalResponse("PAN Number :");
	for(u8_counter=2;u8_counter<11;u8_counter++)
	{
		USART_Transmit(CustomerData[u8_counter]);
	}
	APP_APPToTerminalResponse("\r");
	APP_APPToTerminalResponse("Balance :");
	/* display balance */
	for(u8_counter=11;u8_counter<19;u8_counter++)
	{
		USART_Transmit(CustomerData[u8_counter]);
	}
	APP_APPToTerminalResponse("\r");
	APP_APPToTerminalResponse("*************************************************************\r");
	return NO_ERROR;
}

uint8_t APP_displayAllCustomer(void)
{
	uint16_t u16_counter=0;
	uint16_t u16_CustomesNumber=0;
	/* Get total number of customers */
	/* first read Total number */
	u16_CustomesNumber = APP_NumberofStoredCustomers();
	if (u16_CustomesNumber ==0)
	{
		APP_APPToTerminalResponse("****************************************************\r");
		APP_APPToTerminalResponse("Data base is empty !! \r");
		APP_APPToTerminalResponse("****************************************************\r");
		return NO_ERROR;
		
	}
	APP_APPToTerminalResponse("Total number of customers is : ");
	APP_DisplayTotNumOfCustomers();
	APP_APPToTerminalResponse("\r");
	APP_APPToTerminalResponse("*******************************************************\r");
	
	
	for(u16_counter=1;u16_counter<=u16_CustomesNumber;u16_counter++)
	{
		APP_ReadCustomerDataByID(u16_counter);
		APP_DisplayCustomerDatafromBuffer();
	}
	APP_APPToTerminalResponse("*************************************************************\r");
}
uint8_t APP_ATMStatuscheck(void)
{
   float fMAXAmount;
	/* get max amount from Data base */
	APP_GetMaxAmountFromDB();
	
	fMAXAmount = APP_stringToFloat(MAXamountBuffer,8);
	/*check if max amount is set */
	
	
	if ((int)fMAXAmount !=0 && fMAXAmount != 0xffff)
	{
		return NO_ERROR;
	}
	return ERROR;
}
