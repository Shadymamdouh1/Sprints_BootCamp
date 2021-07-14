/*
 * DIO Driver.c
 *
 * Created: 7/14/2021 11:49:44 AM
 * Author : Shady Mamdouh 
 */ 

#include <avr/io.h>
#include "Dio.h"
#include "types.h"



int main(void)
{   // set port A pin 0 as output and has initial value 1
	strDio_pins[0].u8_PortNum=PORT_A;
	strDio_pins[0].u8_Direction=DIO_PIN_DIR_OUTPUT;
	strDio_pins[0].u8_PinNum=PIN_0;  
	strDio_pins[0].u8_InitState=PIN_HIGH;
	Dio_init(&strDio_pins[0]);
	//PORT C PIN 0 AS input
	strDio_pins[16].u8_PortNum=PORT_C;
	strDio_pins[16].u8_Direction=DIO_PIN_DIR_INPUT;
	strDio_pins[16].u8_PinNum=PIN_0;
	strDio_pins[16].u8_InitState=PIN_HIGH;
	Dio_init(&strDio_pins[16]);
	//
	// set port B pin 0 as output and has initial value 0
	strDio_pins[8].u8_PortNum=PORT_B;
	strDio_pins[8].u8_Direction=DIO_PIN_DIR_OUTPUT;
	strDio_pins[8].u8_PinNum=PIN_0;
	strDio_pins[8].u8_InitState=PIN_LOW;
	Dio_init(&strDio_pins[8]);
	
	 uint8_t u8_value;
    /* Replace with your application code */
    while (1) 
    {
		Dio_readPin(16,&u8_value);
		Dio_writePin(8,u8_value);
		
		
    }
}

