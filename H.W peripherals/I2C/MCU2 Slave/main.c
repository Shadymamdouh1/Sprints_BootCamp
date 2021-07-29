/*
 * I2C slave.c
 *
 * Created: 7/26/2021 3:56:33 PM
 * Author : Shady mamdouh 
 */ 
#include "register.h"
#include "types.h"
#include "i2c.h"


int main(void)
{  
	DDRA |=(1<<0);
	uint8_t dataReceived;
	uint8_t dataSend =30;
	uint8_t MyAddress =2;
	MCAL_I2CSlaveInit(MyAddress);
	MCAL_I2CSlaveListen();
	MCAL_I2CSlaveReceive(&dataReceived);
	MCAL_I2CSlaveListen();
	
	MCAL_I2CSlaveTransmit(&dataSend);
	
    if (dataReceived==20)
    {
	    PORTA |=(1<<0);
    }
    while (1) 
    {
    }
}

