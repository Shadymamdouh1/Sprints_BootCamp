/*
 * EEPROM.c
 *
 * Created: 7/29/2021 2:11:14 PM
 *  Author: Shady Mamdouh
 */ 
/************Includes************************************************/
#include "types.h"
#include "..\..\MCAL\I2C\i2c.h"
#include "EEPROM.h"
/********************************************************************/

void ECUAL_EEPROMInit(void)
{
	/* MCU Configured as a Master */
	Master_Configure_t.Master_ADDRESS=1;
	Master_Configure_t.TWBR_VALUE=10;
	Master_Configure_t.TWPS_PRESCAL_VAL=NO_PRESCALE;
	MCAL_I2CMasterInit(&Master_Configure_t);
	
}  
                        /* 0,1,2*/
void ECUAL_EEPROMWrite(uint8_t EEPROM_PageNum, uint8_t u8_MEMAddress , uint8_t u8_DataWrite)
{
	/* initialize EEPROM control byte */
	uint8_t u8_ControlByte =0;
	/* The 4 MSB of EEPROM Control byte should be 1010 representing read/write operation */
	u8_ControlByte =(0b1010<<3)|(EEPROM_PageNum<<0);  // zero in LSB that represent Write operation will be initialized automatically by i2c function
		
	/* initiate the start condition with control byte */
	MCAL_I2CMaterEstablishComm(u8_ControlByte);
	
	/* memory address in EEPROM */
	MCAL_I2CMasterWrightData(&u8_MEMAddress);
	
	/* write data into the address */
	MCAL_I2CMasterWrightData(&u8_DataWrite);
	
	/* send stop condition */
	MCAL_I2CMasterStopCondition();
}

void ECUAL_EEPROMRead(uint8_t EEPROM_PageNum, uint8_t u8_MEMAddress , uint8_t *u8_DataRead)
{
	/* initialize EEPROM control byte */
	uint8_t u8_ControlByte =0;
	/* The 4 MSB of EEPROM Control byte should be 1010 representing read/write operation */
	u8_ControlByte =(0b1010<<3)|(EEPROM_PageNum<<0);  // zero in LSB that represent Write operation will be initialized automatically by i2c function
	
	/* initiate the start condition with control byte */
	MCAL_I2CMaterEstablishComm(u8_ControlByte);
	
	/* memory address in EEPROM */
	MCAL_I2CMasterWrightData(&u8_MEMAddress);
	
	
	
	/* repeated start to read */
	MCAL_I2CMasterRepeatedStart(u8_ControlByte);
	
	/* Small delay */
	uint32_t counter;
	for (counter=0;counter<5000;counter++);
	
	/* Read Data */
	MCAL_I2CMasterReadsendNACK(u8_DataRead);
	
	/* send stop condition */
	MCAL_I2CMasterStopCondition();
}