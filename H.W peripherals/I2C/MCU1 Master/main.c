/*
 * I2C Driver.c
 *
 * Created: 7/26/2021 12:03:42 PM
 * Author : Shady Mamdouh
 */ 
#include "types.h"
#include "i2c.h"
#include "register.h"

int main(void)
{   DDRA |=(1<<0);
	uint8_t SALVE_ADD=2;
	uint8_t data =20;
	uint8_t receivedData=0;
	/********master config****************/
	Master_Configure_t.Master_ADDRESS=0;
	Master_Configure_t.TWBR_VALUE=8;
	Master_Configure_t.TWBR_VALUE=NO_PRESCALE;
	/********************************************/
	MCAL_I2CMasterInit(&Master_Configure_t);
	MCAL_I2CMaterEstablishComm(SALVE_ADD);
	MCAL_I2CMasterWrightData(&data);
	MCAL_I2CMasterRepeatedStart(SALVE_ADD);
	//delay
	uint32_t counter;
	for (counter=0;counter<5000;counter++);
	MCAL_I2CMasterReadsendACK(&receivedData);
	//PORTA = receivedData;
	MCAL_I2CMasterStopCondition();
	
	if (receivedData == 30)
	{
		PORTA |=(1<<0);
	}
	
    
    while (1) 
    {
    }
}

