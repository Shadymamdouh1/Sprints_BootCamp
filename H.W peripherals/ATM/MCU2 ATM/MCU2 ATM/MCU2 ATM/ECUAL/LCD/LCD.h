/*
 * LCD.h
 *
 * Created: 4/25/2021 2:55:51 AM
 *  Author: Shady mamdouh
 */ 


#ifndef LCD_H_
#define LCD_H_


/*********************LCD PORT*****************************************/
#define LCD_Port PORT_A 
 /* CONTROL PINS */
#define LCD_SR_bit 1
#define LCD_RW_bit 2  
#define LCD_EN_bit 3   
/****************************LCD COMMANDS*****************************/

#define LCD_mode_8bit_1line		0x30
#define LCD_mode_8bit_2line		0x38
#define LCD_mode_4bit_1line		0x20
#define LCD_mode_4bit_2line		0x28
#define LCD_ENTRY_INC_MODE		0x06
#define LCD_DIS_OFF_CURSOR_OFF  0X08
#define LCD_DIS_ON_CURSOR_ON	0X0E
#define LCD_DIS_ON_CURSOR_OFF	0X0C
#define LCD_DIS_ON_CURSOR_BLINK 0X0F
#define LCD_DIS_SHIFT_LEFT		0X18
#define LCD_DIS_SHIFT_RIGHT		0X1C
#define LCD_MOVE_CURSOR_LEFT	0X10
#define LCD_MOVE_CURSOR_RIGHT	0X14
#define LCD_CLR_DIS_AND_DDRAM	0X01
#define LCD_cursor_line1		0x80
#define LCD_cursor_line2		0XC0
/***********************************************************************************/
//									APIs
/*********************************************************************************
* Name : LCD_init
* Description : initialize the LCD in 4 Bits mode and 5*8 mode 
*/
void LCD_init(void);
/**********************************************************************************
* Name : LCD_send_command
* Description : used to sent a command to LCD
*/
void LCD_send_command(uint8_t command);
/*********************************************************************************
* Name : LCD_Kick
* Description : used to Enable the Enable pin of the LCD and Disable it again
*/
void LCD_Kick(void);
/*********************************************************************************
* Name : LCD_clear_screen
* Description : used to Clear the screen 
*/
void LCD_clear_screen(void);
/*********************************************************************************
* Name : LCD_GoTo_xy
* Description : used to Jump to a specific location 
*/
void LCD_GoTo_xy(uint8_t row, uint8_t position);
/*********************************************************************************
* Name : LCD_display_charcter
* Description : used to Display a character on the LCD
*/
void LCD_display_charcter(uint8_t data);
/*********************************************************************************
* Name : LCD_display_String
* Description : used to Display a string on the LCD
*/
void LCD_display_String(uint8_t *string);
/*********************************************************************************
* Name : LCD_DisplayInteger
* Description : used to Display an integer number on the LCD
*/
void LCD_DisplayInteger(uint32_t u32_number);
/*********************************************************************************
* Name : LCD_DisplayFloat
* Description : used to Display a float number on the LCD
*/
void LCD_DisplayFloat(float f32_floatNumber);
/*********************************************************************************/
#endif /* LCD_H_ */