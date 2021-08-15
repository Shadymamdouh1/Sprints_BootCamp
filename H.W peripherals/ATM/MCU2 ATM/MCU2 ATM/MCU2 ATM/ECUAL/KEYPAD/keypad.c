/*
 * keypad.c
 *
 * Created: 4/25/2021 8:52:56 PM
 *  Author: Shady mamdouh
 */ 
#include "types.h"
#include "..\..\MCAL\DIO\DIO.h"
#include "keypad.h"

uint8_t keypad_row[]={R0,R1,R2,R3};
uint8_t keypad_col[]={C0,C1,C2,C3};
void keyPad_init(void)
{  
	
	strDio_pins.u8_PortNum=keypadROWS_port;
	strDio_pins.u8_PinNum=R0;
	strDio_pins.u8_Direction=DIO_PIN_DIR_INPUT;
	Dio_init(&strDio_pins);
	
	strDio_pins.u8_PortNum=keypadROWS_port;
	strDio_pins.u8_PinNum=R1;
	strDio_pins.u8_Direction=DIO_PIN_DIR_INPUT;
	Dio_init(&strDio_pins);
	
	strDio_pins.u8_PortNum=keypadROWS_port;
	strDio_pins.u8_PinNum=R2;
	strDio_pins.u8_Direction=DIO_PIN_DIR_INPUT;
	Dio_init(&strDio_pins);
	
	strDio_pins.u8_PortNum=keypadROWS_port;
	strDio_pins.u8_PinNum=R3;
	strDio_pins.u8_Direction=DIO_PIN_DIR_INPUT;
	Dio_init(&strDio_pins);
	
	// second 4 pins are output 
	strDio_pins.u8_PortNum=keypadColumns_port;
	strDio_pins.u8_PinNum=C0;
	strDio_pins.u8_Direction=DIO_PIN_DIR_OUTPUT;
	Dio_init(&strDio_pins);
	
	strDio_pins.u8_PortNum=keypadColumns_port;
	strDio_pins.u8_PinNum=C1;
	strDio_pins.u8_Direction=DIO_PIN_DIR_OUTPUT;
	Dio_init(&strDio_pins);
	
	strDio_pins.u8_PortNum=keypadColumns_port;
	strDio_pins.u8_PinNum=C2;
	strDio_pins.u8_Direction=DIO_PIN_DIR_OUTPUT;
	Dio_init(&strDio_pins);
	
	strDio_pins.u8_PortNum=keypadColumns_port;
	strDio_pins.u8_PinNum=C3;
	strDio_pins.u8_Direction=DIO_PIN_DIR_OUTPUT;
	Dio_init(&strDio_pins);
	
	// pull up rows PINS
	Dio_writePin(keypadROWS_port,R0,PIN_HIGH);
	Dio_writePin(keypadROWS_port,R1,PIN_HIGH);
	Dio_writePin(keypadROWS_port,R2,PIN_HIGH);
	Dio_writePin(keypadROWS_port,R3,PIN_HIGH);
	//DIO_WritePort(keypad_port,0XFF);
}
uint8_t keyPad_GetKey(void)
{
	int i,j;
	for(i=0;i<4;i++)
	{
		
		Dio_writePin(keypadColumns_port,C0,PIN_HIGH);
		Dio_writePin(keypadColumns_port,C1,PIN_HIGH);
		Dio_writePin(keypadColumns_port,C2,PIN_HIGH);
		Dio_writePin(keypadColumns_port,C3,PIN_HIGH);
		
		Dio_writePin(keypadColumns_port,keypad_col[i],PIN_LOW);
		uint8_t u8_temp ;
		for(j=0;j<4;j++)
		{
			Dio_readPin(keypadROWS_port,keypad_row[j],&u8_temp);
			if(u8_temp ==0)
			   {
				   
				while(u8_temp==0)    //single pressed
				 {
					 Dio_readPin(keypadROWS_port,keypad_row[j],&u8_temp);
				}                     
				switch(i)
				{
					case 0 :
						{
							if(j == 0) return '7';
							else if(j == 1) return '4';
							else if(j == 2) return '1';
							else if(j == 3) return '?';
							break;
						}
					case 1 :
					   {
						    if(j == 0) return '8';
						    else if(j == 1) return '5';
						    else if(j == 2) return '2';
						    else if(j == 3) return '0';
						    break;
					    }
					case 2 :
					   {
						    if(j == 0) return '9';
						    else if(j == 1) return '6';
						    else if(j == 2) return '3';
						    else if(j == 3) return '=';
						    break;
					   }
					case 3 :
					{
						if(j == 0) return '/';
						else if(j == 1) return '*';
						else if(j == 2) return '-';
						else if(j == 3) return '+';
						break;
					}
					
				}
			}
		}
	}
	return 'A';  // return A if no key is pressed 
}