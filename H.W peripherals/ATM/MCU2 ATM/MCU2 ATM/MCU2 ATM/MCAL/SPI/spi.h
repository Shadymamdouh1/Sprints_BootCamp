/*
 * spi.h
 *
 * Created: 7/23/2021 3:22:12 PM
 *  Author: Shady Mamdouh
 */ 


#ifndef SPI_H_
#define SPI_H_
/****************frequancy selection**************************/
typedef enum enFreqSelection_t
{
	Fosc_4,
	Fosc_16,
	Fosc_64,
	Fosc_128
	
}enFreqSelection_t;
/******************** Operation Modes******************************/
#define MASTER_MODE 1
#define SLAVE_MODE 0
/**********************frequancy speed modes***********************/
#define NORMAL_SPEED 0
#define DOUBLE_SPEED 1
/************************PINS MACROS******************************/
#define SPCR_SPR0 0
#define SPCR_SPR1 1
#define SPCR_CPHA 2
#define SPCR_CPOL 3
#define SPCR_MSTR 4
#define SPCR_DORD 5
#define SPCR_SPE  6
#define SPCR_SPIE 7

#define SPSR_SPI2X 0
#define SPSR_WCOL 6
#define SPSR_SPIF 7

#define PB_SS 4
#define PB_MOSI 5
#define PB_MISO 6
#define PB_SCK 7
/*****************************************************************/
/**********************************************************************************************
*										APIs
***********************************************************************************************
* Name : MCAL_SpiInit
* Description : initialize the SPI configuration according to 
                spiConfig.h file 
*/
void MCAL_SpiInit(void);
/***************************************************************************
* Name : MCAL_SPIMasterTXRX
* Description : this function is used by master to transmit and receive 1 byte at same time
				it takes 2 pointers to data send and data received
*/
void MCAL_SPIMasterTXRX(uint8_t *u8_DataSend, uint8_t *u8_DataReceive);
/********************************************************************************************
* Name : MCAL_SPISlaveTXRX
* Description : this function is used by slave to transmit and receive 1 byte at same time
                it takes 2 pointers to data send and data received
*/
void MCAL_SPISlaveTXRX(uint8_t *u8_DataSend, uint8_t *u8_DataReceive);
/*******************************************************************************************
* Name : MCAL_SPIMasterTrans_String
* Description :  this function is used by master to transmit string with max size of 255 char
*/
void MCAL_SPIMasterTrans_String(uint8_t *u8_StringSend);
/*******************************************************************************************
* Name : MCAL_SPIMasterReceive_String
* Description : this function is used by master to receive string with max size of 255 char
*/
void MCAL_SPIMasterReceive_String(uint8_t *u8_StringReceive);
/*******************************************************************************************
* Name : MCAL_SPISlaveTrans_String
* Description : this function is used by slave to transmit string with max size of 255 char
*/
void MCAL_SPISlaveTrans_String(uint8_t *u8_StringSend);
/*******************************************************************************************
* Name : MCAL_SPISlaveReceive_String
* Description :  this function is used by slave to receive string with max size of 255 char
*/
void MCAL_SPISlaveReceive_String(uint8_t *u8_StringReceive);
/*******************************************************************************************
* NAME : MCAL_SPISlaveINTDriven
* Description : CAll the passed function once the interrupt rises 
                the ISR disables the interrupt after it happens so you should enable it again
				in the called function
*/
void MCAL_SPISlaveINTDriven(void(*ptr)(void));
/********************************************************************************************
* NAME : MCAL_SPI_EnableInterrupts
* Description : Enable SPI and global Interrupts
*/
void MCAL_SPI_EnableInterrupts(void);
/********************************************************************************************
* NAME : MCAL_SPI_EnableInterrupts
* Description : Disables  SPIE  Interrupt only
*/
void MCAL_SPI_DisableInterrupt(void);
/********************************************************************************************/
void MCAL_SPISlaveTrans(uint8_t DataTrans);
void MCAL_SPIMasterReceive(uint8_t *ReceivedData);
#endif /* SPI_H_ */