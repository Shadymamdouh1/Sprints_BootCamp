/*
 * EEPROM.h
 *
 * Created: 7/29/2021 2:11:32 PM
 *  Author: Shady Mamdouh
 */ 


#ifndef EEPROM_H_
#define EEPROM_H_
/************************************INCLUDES*********************************************/
#include "types.h"
/*****************************************************************************************
*									     APIs
******************************************************************************************
* Name : ECUAL_EEPROMInit
* Description : initialize the EEPROM Module and I2C interface
*/
void ECUAL_EEPROMInit(void);
/******************************************************************************************
* Name : ECUAL_EEPROMWrite
* Description : it takes Page number inside EEPROM(0,1,2) and Memory loc inside the Page
				and the Data to be Written 
*/
void ECUAL_EEPROMWrite(uint8_t EEPROM_PageNum, uint8_t u8_MEMAddress , uint8_t u8_Data);
/******************************************************************************************
* Name : ECUAL_EEPROMRead
* Description : it takes Page number inside EEPROM(0,1,2) and Memory loc inside the Page
				and it returns the  Data to from this location
*/
void ECUAL_EEPROMRead(uint8_t EEPROM_PageNum, uint8_t u8_MEMAddress , uint8_t *u8_DataRead);
/*******************************************************************************************/
#endif /* EEPROM_H_ */