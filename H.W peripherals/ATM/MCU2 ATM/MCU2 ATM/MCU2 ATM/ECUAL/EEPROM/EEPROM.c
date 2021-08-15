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
	Master_Configure_t.TWBR_VALUE=100;
	Master_Configure_t.TWPS_PRESCAL_VAL=NO_PRESCALE;
	MCAL_I2CMasterInit(&Master_Configure_t);
	
}  
                        
void ECUAL_EEPROMWrite( uint16_t u16_MEMAddress , uint8_t u8_DataWrite)
{
	/* the First word address the MSB 8 bits of the address */ 
	uint8_t u8_FW_ADD =(uint8_t)(u16_MEMAddress>>8);
	/* second word address the LSB 8 bits of the address */
	uint8_t u8_SW_ADD=(uint8_t)(u16_MEMAddress);
	
	/* initialize EEPROM control byte */
	uint8_t u8_ControlByte =0b01010000;  //1010 then 000 slave address then 0 for write operation
	// this byte will be shifted in i2c write will be 10100000 and for repeat start 10100001
	
		
	/* initiate the start condition with control byte */
	MCAL_I2CMaterEstablishComm(u8_ControlByte);
	
	/*first word memory address in EEPROM */
	MCAL_I2CMasterWrightData(&u8_FW_ADD);
	
	/*first word memory address in EEPROM */
	MCAL_I2CMasterWrightData(&u8_SW_ADD);
	
	/* write data into the address */
	MCAL_I2CMasterWrightData(&u8_DataWrite);
	
	/* send stop condition */
	MCAL_I2CMasterStopCondition();
}

void ECUAL_EEPROMRead( uint16_t u16_MEMAddress , uint8_t *u8_DataRead)
{
	
	
	/* initialize EEPROM control byte */
	 uint8_t u8_ControlByte =0b01010000;  //1010 then 000 slave address then 0 for write operation  
	                                     // this byte will be shifted in i2c write will be 10100000 and for repeat start 10100001
	/* the First word address the MSB 8 bits of the address */
	uint8_t u8_FW_ADD =(uint8_t)(u16_MEMAddress>>8);
	/* second word address the LSB 8 bits of the address */
	uint8_t u8_SW_ADD=(uint8_t)(u16_MEMAddress);
	
	
	
	/* initiate the start condition with control byte */
	MCAL_I2CMaterEstablishComm(u8_ControlByte);
	
	/*first word memory address in EEPROM */
	MCAL_I2CMasterWrightData(&u8_FW_ADD);
	
	/*first word memory address in EEPROM */
	MCAL_I2CMasterWrightData(&u8_SW_ADD);
	
	
	
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