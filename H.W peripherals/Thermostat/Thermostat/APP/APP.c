/*
 * APP.c
 *
 * Created: 8/3/2021 7:55:16 PM
 *  Author: Shady Mamdouh
 */ 
/**************INCLUDES*****************/
#include "types.h"
#include "..\ECUAL\KEYPAD\keypad.h"
#include "..\ECUAL\LCD\LCD.h"
#include "..\ECUAL\MOTOR\motor.h"
#include "..\ECUAL\TempSensor_LM35\TempSensor.h"
#include "APP.h"
/********************************************************/
/* array to hold Temp value entered by the keypad */
uint8_t TEMP_String[3];
/* var to hold the temp value after convert to int val */
uint8_t gu8_MaxTemp;
/* var to hold the the input temp of the temp sensor */
uint8_t gu8_ReadTemp;
void APP_APPInit(void)
{
	/* initialize LCD */
	LCD_init();
	/* initialize KEYPAD   */
	keyPad_init();
	/* initialize TEMP sensor */
	TempSensorInit(TEMP_SENSOR_CHANNEL,TEMP_SENSOR_VREF);
	/* initialize motor */
	MotorInit();
	uint8_t u8_counter=0 ;
	LCD_display_String("Enter Temp value");
	uint8_t KEY;
	uint8_t temp;
	while(u8_counter !=2)
	{
		KEY=keyPad_GetKey();
		if (KEY !='A')
		{
			TEMP_String[u8_counter]=KEY;
			u8_counter++;
			LCD_display_charcter(KEY);
		}
		else
		{
			continue;
		}
	}
	TEMP_String[2]='C';
	/* convert from temp string to integer number */
	temp=((TEMP_String[0]-48)*10)+(TEMP_String[1]-48);
	LCD_clear_screen();
	LCD_GoTo_xy(0,0);
	
	LCD_display_String("Max Temp is:");
	LCD_GoTo_xy(1,0);
	LCD_display_String(TEMP_String);
	
	gu8_MaxTemp =temp;
	
	
	
}

void APP_GetState(void)
{
	
	/* read temp */
	TempSensorGetTemp(&gu8_ReadTemp);
	
}
void APP_UpdateState(void)
{
	/* check the max */
	if (gu8_ReadTemp>=gu8_MaxTemp)
	{
		MotorON();
	}
	else
	{
		MotorOFF();
		
	}
}