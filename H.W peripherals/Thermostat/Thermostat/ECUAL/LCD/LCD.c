/*
 * LCD.c
 *
 * Created: 4/25/2021 2:55:25 AM
 *  Author: Shady mamdouh
 */ 
#include "types.h"
#include "LCD.h"
#include "..\..\MCAL\TIMER\timer.h"
#include "..\..\MCAL\DIO\DIO.h"

void LCD_init(void)
{
	/* timer initialize */
	GptInit();
	
	/***************************************************/
	DIO_SetPortDirection(LCD_Port,DIO_PIN_DIR_OUTPUT);
	/* return the Px0 to input */
	strDio_pins.u8_PortNum=LCD_Port;
	strDio_pins.u8_PinNum=PIN_0;
	strDio_pins.u8_Direction=DIO_PIN_DIR_INPUT;
	Dio_init(&strDio_pins);
	/**********************************************/
	Dio_writePin(LCD_Port,LCD_RW_bit,PIN_LOW);
	Dio_writePin(LCD_Port,LCD_EN_bit,PIN_LOW);
	Dio_writePin(LCD_Port,LCD_SR_bit,PIN_LOW);
	
	/* delay 20 ms */
	GptStart_Sync(TIMER0,20000);
	LCD_send_command(0x33);
	
	GptStart_Sync(TIMER0,5000);
	LCD_send_command(0x32);
	/* delay 5 ms */
	GptStart_Sync(TIMER0,5000);
	
	LCD_send_command(LCD_mode_4bit_2line);
	LCD_send_command(LCD_DIS_ON_CURSOR_OFF);
	LCD_send_command(LCD_ENTRY_INC_MODE);
	LCD_send_command(0x01);
	
	
}



void LCD_send_command(uint8_t command)
{   

	
	/* Clear Port */
	DIO_WritePort(LCD_Port,0);
	DIO_WritePort(LCD_Port,(command & 0xF0));  //  first 4 MSB bits only will be taken
	  Dio_writePin(LCD_Port,LCD_SR_bit,PIN_LOW); // SR =0
	  Dio_writePin(LCD_Port,LCD_RW_bit,PIN_LOW); // R/W =0 (WRITE MODE)
	LCD_Kick();
	DIO_WritePort(LCD_Port,0);
	DIO_WritePort(LCD_Port,command<<4);  // second 4 bits after shift left
	Dio_writePin(LCD_Port,LCD_SR_bit,PIN_LOW); // SR =0
	Dio_writePin(LCD_Port,LCD_RW_bit,PIN_LOW); // R/W =0 (WRITE MODE)  
	LCD_Kick();
	
	
	
}
void LCD_Kick(void)
{   
	Dio_writePin(LCD_Port,LCD_EN_bit,PIN_HIGH);
	/* delay 5 ms */
	GptStart_Sync(TIMER0,5000);
	Dio_writePin(LCD_Port,LCD_EN_bit,PIN_LOW);
	
}
void LCD_GoTo_xy(uint8_t u8_row, uint8_t u8_col)
{
	if (u8_row==0)
	{
		LCD_send_command((LCD_cursor_line1+u8_col));
	}
	else if (u8_row==1)
	{
		LCD_send_command(LCD_cursor_line2+u8_col);
	}
}

void LCD_display_charcter(uint8_t data)
{

	
	/*  first 4 MSB bits only will be taken */
	DIO_WritePort(LCD_Port,data & 0xF0);   
	Dio_writePin(LCD_Port,LCD_SR_bit,PIN_HIGH);  // SR =1
	Dio_writePin(LCD_Port,LCD_RW_bit,PIN_LOW);  // R/W =0 (WRITE MODE)
	LCD_Kick();
	/* second 4 bits after shift left */
	DIO_WritePort(LCD_Port,data<<4);   
	Dio_writePin(LCD_Port,LCD_SR_bit,PIN_HIGH);  // SR =1
	Dio_writePin(LCD_Port,LCD_RW_bit,PIN_LOW);  // R/W =0 (WRITE MODE)
	LCD_Kick();
	

}
void LCD_display_String(uint8_t *string)
{
	
	uint8_t count=0;
	while(*string > 0)
	{    
		count++;
		 LCD_display_charcter(*string++);
		if (count ==16)  // first row completed
		{
			LCD_GoTo_xy(1,0);   // row 1 position 0
			
		}
		if (count ==32)       // LCD filled and will be cleared and start again
		{   LCD_clear_screen();
			LCD_GoTo_xy(0,0);   // row 0 position 0
			count=0;
		}
	}
}
uint32_t power(uint8_t base, uint8_t power)
{
	uint32_t u32_result =1;
	if (power==0)
	{
		return 1;
	}
	else if (power==1)
	{
		return base;
	}
	uint8_t u8_counter =0;
	for (u8_counter=0;u8_counter<power;u8_counter++)
	{
		u32_result =u32_result*(base);
	}
	return base;
}
void IntegerTostring(uint32_t u32_number, uint8_t *str)
{
	uint32_t u32_temp;
	uint8_t u8_counter=0;
	u32_temp =u32_number;
	if (u32_number==0)
	{
		str[1]='\0';
		str[0]=48;
	}
	else
	{
		
	
	while(u32_temp !=0)
	{
		u32_temp = u32_temp /10;
		u8_counter++;
	}
	u32_temp =u32_number;
	str[u8_counter]='\0';
	while(u32_temp !=0)
	{
		str[u8_counter-1]=(u32_temp %10)+48 ;
		u32_temp =u32_temp /10;
		u8_counter--;
	}
	
	}
	
}
void LCD_DisplayInteger(uint32_t u32_number)
{   
	uint8_t arr[10];
	IntegerTostring(u32_number,arr);
	LCD_display_String(arr);
	 
}
void LCD_clear_screen(void)
{
	LCD_send_command(LCD_CLR_DIS_AND_DDRAM);
}
void LCD_DisplayFloat(float f32_floatNumber)
{
	uint32_t u32_intPart = (int)f32_floatNumber;
	uint32_t u32_fraction = (f32_floatNumber - u32_intPart) *100 ;
	LCD_DisplayInteger(u32_intPart);
	LCD_display_charcter('.');
	LCD_DisplayInteger(u32_fraction);
}