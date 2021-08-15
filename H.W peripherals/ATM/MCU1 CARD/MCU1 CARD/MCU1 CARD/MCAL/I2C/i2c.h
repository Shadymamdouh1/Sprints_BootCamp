/*
 * i2c.h
 *
 * Created: 7/26/2021 12:05:05 PM
 *  Author: Shady Mamdouh
 */ 


#ifndef I2C_H_
#define I2C_H_
#define FOSC 1000000UL
/****************TWPS PRE SCALE*************************/
typedef enum TWPS_PRESCALE
{
	NO_PRESCALE,
	PRESCALE_4,
	PRESCALE_16,
	PRESCALE_64
}TWPS_PRESCALE;

/***************BITS **********************************/
#define TWCR_TWEN 2
#define TWCR_TWEA 6
#define TWSR_TWPS0 0
#define TWAR_TWGCE 0
#define TWCR_TWSTA 5
#define TWCR_TWSTO 4
#define TWCR_TWINT 7
/***********************************************************************************
* in configuration structure of master (Master_Configure_t) use one of these options for TWBR_VALUE
* Options :	NO_PRESCALE
			PRESCALE_4
			PRESCALE_16
			PRESCALE_64
* ex Master_Configure_t->TWBR_VALUE=NO_PRESCALE;
* assign the bit rate value and Master address
* finally pass the address of the Master_Configure_t to MCAL_I2CSlaveInit(&Master_Configure_t);
*/
typedef struct Master_config_t
{
	uint8_t TWBR_VALUE;
	uint8_t TWPS_PRESCAL_VAL;
	uint8_t Master_ADDRESS;
	
}Master_config_t;

/***************global var of master config struct to be used by the user**********/
 Master_config_t Master_Configure_t ;
/**********************************************************************************/

/****************************MASTER STATUS CODES**********************************/
typedef enum I2C_status_codes
{
	START_CON_NOT_SENT= 0,
	Start_cond_sent_tx =0x08,
	Repeat_start_sent_tx =0x10,
	SLA_W_sent_ACK_recevied =0x18,
	SLA_W_sent_NOTACK_recevied =0x20,
	SLA_R_sent_ACK_recevied =0x40,
	SLA_R_sent_NOTACK_recevied =0x48,
	Data_sent_ACK_received = 0x28,
	Data_sent_NOTACK_received=0x30,
	Data_received_ACK_sent =0x50,
	Data_received_NOTACK_sent =0x58
	
}I2C_status_codes;
/***********************************SLAVE STATUS CODES*******************************/
typedef enum I2C_slave_status_codes
{
	Own_SLA_W_received_ACK_sent =0x60,
	Arbitration_lost_in_master_SLA_W_received_ACK_sent =0x68,  // Arbitration lost in master In SLA+R/W but slave received SLA+W and return ACK
	SLA_R_received_ACK_sent =0xA8,
	Arbitration_lost_SLA_R_received_ACK_sent=0xB0,
	Gcall_received_ACK_sent = 0x70,
	Arbitration_lost_in_master_GCall_received_ACK_sent =0x78,  // Arbitration lost in master In SLA+R/W but slave received General call and return ACK
	Stop_orRepeatStart_received_while_slave = 0xA0,    // received Stop or repeat Start while still  addressed as a slave
	Data_sent_ACK_Received =0xB8,
	Data_sent_NOTACK_Received =0xC0,
	Last_Data_sent_ACK_received =0xC8,
	SLA_W_add_data_received_ACK_sent =0X80, // previously addressed by its own address , data received ACK sent
	GCall_add_data_received_ACK_sent =0x90,  // previously addressed by general call , data received ACK sent
	GCall_add_data_received_NOTACK_sent =0x98,  // previously addressed by general call , data received NOTACK sent
	SLA_W_add_data_received_NOTACK_sent =0X88,     // previously addressed by its own address , data received NOTACK sent
	
}I2C_slave_status_codes;

/*************************************************************************************************
							          APIS 
**************************************************************************************************/
void MCAL_I2CMasterInit(Master_config_t *MasterConfig);
void MCAL_I2CSlaveInit(uint8_t u8_SlaveAddress);
I2C_status_codes MCAL_I2CMaterEstablishComm(uint8_t u8_slaveAddress);
I2C_status_codes MCAL_I2CMasterRepeatedStart(uint8_t u8_slaveAddress);
I2C_status_codes MCAL_I2CMasterWrightData(uint8_t* u8_Data);
I2C_status_codes MCAL_I2CMasterReadsendACK(uint8_t *readData);
I2C_status_codes MCAL_I2CMasterReadsendNACK(uint8_t *readData);
void MCAL_I2CMasterStopCondition(void);
I2C_slave_status_codes MCAL_I2CSlaveListen(void);
I2C_slave_status_codes MCAL_I2CSlaveTransmit(uint8_t *u8_DataSend);
I2C_slave_status_codes MCAL_I2CSlaveReceive(uint8_t *ReceivedData);


#endif /* I2C_H_ */