/*
 * i2c.c
 *
 * Created: 7/26/2021 12:04:43 PM
 *  Author: Shady Mamdouh 
 */ 
#include "types.h"
#include "i2c.h"
#include "register.h"
void MCAL_I2CMasterInit(Master_config_t *MasterConfig)
{
	
	/* frequency calculations */
	TWSR |=((MasterConfig->TWPS_PRESCAL_VAL)<<TWSR_TWPS0);
	TWBR = MasterConfig->TWBR_VALUE ;
	
    /* Master address in case of multi master */
	TWAR = ((MasterConfig->Master_ADDRESS)<<1);
	  
	   
			 		
}
void MCAL_I2CSlaveInit(uint8_t u8_SlaveAddress)
{
	/* assign Slave Address */
	TWAR = (u8_SlaveAddress<<1);
	
	/* Enable I2C, clear Flag and Enable ACK */
	TWCR= (1<<TWCR_TWEA)|(1<<TWCR_TWEN)|(1<<TWCR_TWINT);
}
I2C_status_codes MCAL_I2CMaterEstablishComm(uint8_t u8_slaveAddress)
{   
	uint8_t u8State_reg=0;
	
	/* Clear the TWINT Flag, Start condition, Enable I2C */
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);
	
	
	/* wait the flag */
	while(!(TWCR &(1<<TWCR_TWINT)));
	
	
	/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
	u8State_reg =TWSR & 0xF8;
	
	/* check if start condition is sent */		
	if(u8State_reg!=Start_cond_sent_tx)
	{
		return START_CON_NOT_SENT;
	}		
				
	
	/* send SLA+W  W : LOW */
	u8_slaveAddress=(u8_slaveAddress<<1);
	TWDR = u8_slaveAddress & 0b11111110 ;
	
	/* Clear the TWINT Flag by writing 1 and enable I2c */   
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWEN);
	
	/* wait to the flag */
	while(!(TWCR &(1<<TWCR_TWINT)));
		
		/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
		u8State_reg =TWSR & 0xF8;
		
		/* check if slave add+W is sent  */
		if(u8State_reg==SLA_W_sent_ACK_recevied)
		{
			return SLA_W_sent_ACK_recevied;
		}
		/* NACK received */
		else if (u8State_reg==SLA_W_sent_NOTACK_recevied)
		{
			return SLA_W_sent_NOTACK_recevied;
		}
		
}
I2C_status_codes MCAL_I2CMasterRepeatedStart(uint8_t u8_slaveAddress)
{
	uint8_t u8State_reg=0;
	
	/* Clear the TWINT Flag, Start condition, Enable I2C */
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWSTA)|(1<<TWCR_TWEN);
	
	
	/* wait the flag */
	while(!(TWCR &(1<<TWCR_TWINT)));
	
	
	/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
	u8State_reg =TWSR & 0xF8;
	
	/* check if start condition is sent */
	if(u8State_reg!=Repeat_start_sent_tx)
	{
		return START_CON_NOT_SENT;
	}
	
	/* send SLA+R  R : HIGH */
	u8_slaveAddress = (u8_slaveAddress<<1);
	u8_slaveAddress |=(1<<0);
	TWDR =u8_slaveAddress;
	
	/* Clear the TWINT Flag by writing 1 and enable I2c */
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWEN);
	
	/* wait the flag */
	while(!(TWCR &(1<<TWCR_TWINT)));
	
	/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
	u8State_reg =TWSR & 0xF8;
	
	/* check if SLA_R Sent ACK received */
	if(u8State_reg==SLA_R_sent_ACK_recevied)
	{
		return SLA_R_sent_ACK_recevied;
	}
	else if (u8State_reg==SLA_R_sent_NOTACK_recevied)
	{
		
		return SLA_R_sent_NOTACK_recevied;
	}
	
}
I2C_status_codes MCAL_I2CMasterWrightData(uint8_t* u8_Data)
{
	uint8_t u8State_reg=0;
	/* load the data */
	TWDR = *u8_Data;
	
	/* Clear the TWINT Flag by writing 1 and enable I2c */
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWEN);
	
	/* wait the flag */
	while(!(TWCR &(1<<TWCR_TWINT)));
	
	/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
	u8State_reg =TWSR & 0xF8;
	
	if (u8State_reg==Data_sent_ACK_received)
	{
		return Data_sent_ACK_received;
	}
	else if (u8State_reg==Data_sent_NOTACK_received)
	{
		return Data_sent_NOTACK_received;
	}
}
I2C_status_codes MCAL_I2CMasterReadsendACK(uint8_t *readData)
{
	uint8_t u8State_reg=0;
	/* Clear the TWINT Flag by writing 1, enable I2c and Enable ACK generator */
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWEN)|(1<<TWCR_TWEA);
	
	/* wait the flag */
	while(!(TWCR &(1<<TWCR_TWINT)));
	
	*readData =TWDR;
	
	/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
	u8State_reg =TWSR & 0xF8;
	
	if (u8State_reg==Data_received_ACK_sent)
	{
		
		return Data_received_ACK_sent;
	}
	else if (u8State_reg==Data_received_NOTACK_sent)
	{
		return Data_received_NOTACK_sent;
	}
	
}
I2C_status_codes MCAL_I2CMasterReadsendNACK(uint8_t *readData)
{
	uint8_t u8State_reg=0;
	/* Clear the TWINT Flag by writing 1 and enable I2c  */
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWEN);
	
	/* wait the flag */
	while(!(TWCR &(1<<TWCR_TWINT)));
	
	//PORTA=TWDR;
	*readData =TWDR;
	//PORTA = *readData;
	/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
	u8State_reg =TWSR & 0xF8;
	
	if (u8State_reg==Data_received_NOTACK_sent)
	{
		
		return Data_received_NOTACK_sent;
	}
	
	
}
void MCAL_I2CMasterStopCondition(void)
{
	
	/* Clear the TWINT Flag by writing 1 and enable I2c Enable stop condition  */
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWEN)|(1<<TWCR_TWSTO);
	
	/* wait the stop condition finished */ 
	while(TWCR&(1<<TWCR_TWSTO));
	
}
I2C_slave_status_codes MCAL_I2CSlaveListen(void)
{   
	/* slave always listen to bus waiting to be addressed by the Master*/
	while(1)
	{
		uint8_t u8State_reg=0;
		
		/* wait the flag */
		while(!(TWCR &(1<<TWCR_TWINT)));
		
		/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
		u8State_reg =TWSR & 0xF8;
		
		if (u8State_reg==Own_SLA_W_received_ACK_sent)
		{
			return Own_SLA_W_received_ACK_sent;
		}
		if (u8State_reg==Arbitration_lost_in_master_SLA_W_received_ACK_sent)
		{
			return Arbitration_lost_in_master_SLA_W_received_ACK_sent;
		}
		if (u8State_reg==SLA_R_received_ACK_sent)
		{
			return SLA_R_received_ACK_sent;
		}
		if (u8State_reg==Arbitration_lost_SLA_R_received_ACK_sent)
		{
			return Arbitration_lost_SLA_R_received_ACK_sent;
		}
		if (u8State_reg==Gcall_received_ACK_sent)
		{
			return Gcall_received_ACK_sent;
		}
		if (u8State_reg==Arbitration_lost_in_master_GCall_received_ACK_sent)
		{
			return Arbitration_lost_in_master_GCall_received_ACK_sent;
		}
		else
		{
			continue;
		}
	}
	
}
I2C_slave_status_codes MCAL_I2CSlaveTransmit(uint8_t *u8_DataSend)
{
	uint8_t u8State_reg=0;
	
	TWDR = *u8_DataSend;
	
	/* Clear the TWINT Flag by writing 1 and enable I2c enable ACK */
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWEN)|(1<<TWCR_TWEA);
    
	/* wait the flag */
	while(!(TWCR &(1<<TWCR_TWINT)));
	
	/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
	u8State_reg =TWSR & 0xF8;
	
	if (u8State_reg==Stop_orRepeatStart_received_while_slave)
	{   
		/* clear flag */
		TWCR |=(1<<TWCR_TWINT);
		return Stop_orRepeatStart_received_while_slave;
	}
	if (u8State_reg==Data_sent_ACK_Received)
	{
		return Data_sent_ACK_Received;
	}
	if (u8State_reg==Data_sent_NOTACK_Received)
	{
		/* clear flag */
		TWCR |=(1<<TWCR_TWINT);
		return Data_sent_NOTACK_Received;
	}
	if (u8State_reg==Last_Data_sent_ACK_received)
	{
		return  Last_Data_sent_ACK_received;
	}
	
}
I2C_slave_status_codes MCAL_I2CSlaveReceive(uint8_t *ReceivedData)
{
	uint8_t u8State_reg=0;
	
	/* Clear the TWINT Flag by writing 1 and enable I2c enable ACK */
	TWCR =(1<<TWCR_TWINT)|(1<<TWCR_TWEN)|(1<<TWCR_TWEA);
	
	/* wait the flag */
	while(!(TWCR &(1<<TWCR_TWINT)));
	
	/* Read TWI status register the 0XF8 to clear the first LSB 3 bits */
	u8State_reg =TWSR & 0xF8;
	
	if (u8State_reg==SLA_W_add_data_received_ACK_sent)
	{
		*ReceivedData =TWDR;
		return SLA_W_add_data_received_ACK_sent;
	}
	if (u8State_reg==GCall_add_data_received_ACK_sent)
	{
		*ReceivedData =TWDR;
		return GCall_add_data_received_ACK_sent;
	}
	if (u8State_reg== GCall_add_data_received_NOTACK_sent)
	{
		/* clear flag */
		TWCR |=(1<<TWCR_TWINT);
		return GCall_add_data_received_NOTACK_sent;
	}
	

}