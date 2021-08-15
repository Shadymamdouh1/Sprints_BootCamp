/*
 * spi.c
 *
 * Created: 7/23/2021 3:21:34 PM
 *  Author: Shady Mamdouh
 */ 
/***********includes*****************/
#include "types.h"
#include "register.h"
#include "spi.h"
#include "spiConfig.h"
/********************************************************************/
void __vector_12(void) __attribute__((signal,used));
/*******************************************************************/
/*******************************************************************/
void (*pCallBack)(void);
/****************************************************************/

volatile char flush_buffer;
void MCAL_SpiInit(void)
{
	/* Enable SPI  */
	SPCR |=(1<<SPCR_SPE);
	 
	/***********check on operation mode************/
	switch(OPERATION_MODE)
	{
		case MASTER_MODE :
		{
			/* Enable Master Mode */
			
			SPCR |=(1<<SPCR_MSTR);
			
			/*  Assign frequency   */
			// clear bits
			SPCR &=~(0b11<<SPCR_SPR0);
			//set frequency
			SPCR |=(TRANS_FREQ<<SPCR_SPR0);
			
			/* Set Speed  */
			if (FREQ_SPEED==NORMAL_SPEED)
			{
				SPSR &=~(1<<SPSR_SPI2X);
			}
			else if (FREQ_SPEED==DOUBLE_SPEED)
			{
				SPSR |=(1<<SPSR_SPI2X);
			}
			/* PINS Configuration */
			// SS out
			DDRB |=(1<<PB_SS);
			/* hold SS TO HIGH*/
			PORTB |=(1<<PB_SS);
			// MOSI out
			DDRB |=(1<<PB_MOSI);
			//MISO IN
			DDRB &=~(1<<PB_MISO);
			// SCK out
			DDRB |=(1<<PB_SCK);
			
			break;
		}
		
		case SLAVE_MODE :
		{
			/*  Enable Slave Mode  */
			SPCR &=~(1<<SPCR_MSTR);
			
			/* PINS Configuration */
			// SS INPUT
			DDRB &=~(1<<PB_SS);
			// MOSI INPUT
			DDRB &=~(1<<PB_MOSI);
			//MISO OUT
			DDRB |=(1<<PB_MISO);
			// SCK INPUT
			DDRB &=~(1<<PB_SCK);
			break;
		}
	}
	
}
void MCAL_SPIMasterTXRX(uint8_t *u8_DataSend, uint8_t *u8_DataReceive)
{
	uint32_t Counter;
	
	/* apply low signal to SS*/
	   PORTB &=~(1<<PB_SS);
	   
	   /* Small Delay here */
	   for(Counter=0;Counter<1000;Counter++);
	  
   
   /* load data to be send into SPI data reg */
   SPDR = *u8_DataSend;
    
			
   /* wait until flag is set */
   while(!(SPSR &(1<<SPSR_SPIF)));
   
   
   /* received Data   */
   *u8_DataReceive = SPDR;
 
   /* reset SS to High */
   PORTB |=(1<<PB_SS);
   
   /* disable SPI */
  // SPCR &=~(1<<SPCR_SPE);
}
void MCAL_SPISlaveTXRX(uint8_t *u8_DataSend, uint8_t *u8_DataReceive)
{
	
	/* load data to be send into SPI data reg */
	SPDR = *u8_DataSend;
	
	/* wait until flag is set */
	while(!(SPSR &(1<<SPSR_SPIF)));
	
	/* received Data   */
	*u8_DataReceive = SPDR;
	
}
void MCAL_SPIMasterTrans_String(uint8_t *u8_StringSend)
{   
	/* counter for the string */
	uint8_t u8_counter=0;
	
	/* we neglect the received data */
	uint8_t u8_notUsedReceived;
	
	/* loop till the end of the string or max string size  */
	while(u8_StringSend[u8_counter] != '\0' && u8_counter != 254 )
	{
		/* call the MCAL_SPIMasterTXRX to send char by char */
		MCAL_SPIMasterTXRX(&u8_StringSend[u8_counter],&u8_notUsedReceived);
		
		/* increment the counter */
		u8_counter++;
	}
	/* end of the string or max string size  */ 
	if (u8_StringSend[u8_counter] == '\0' || u8_counter == 254)
	{
		MCAL_SPIMasterTXRX(&u8_StringSend[u8_counter],&u8_notUsedReceived);
	}
	
	
	
}
void MCAL_SPIMasterReceive_String(uint8_t *u8_StringReceive)
{
	/* counter for string */
	uint8_t u8_counter=0;
	
	/* unused data send */
	uint8_t u8_UnUsedSend=0;
	
	/* initiate transmission */
	 MCAL_SPIMasterTXRX(&u8_UnUsedSend,&u8_StringReceive[u8_counter]);
	 
	 /* end of string or max string size */
	 while(u8_StringReceive[u8_counter] !='\0' && u8_counter !=254)
	 {
		 /* increment the counter */
		 u8_counter++;
		  MCAL_SPIMasterTXRX(&u8_UnUsedSend,&u8_StringReceive[u8_counter]);
	 }
	
}
void MCAL_SPISlaveTrans_String(uint8_t *u8_StringSend)
{
	/* counter for string */
	uint8_t u8_counter=0;
	
	/* unused data received */
	uint8_t u8_UnUsedReceived=0;
	/* start sending */
	MCAL_SPISlaveTXRX(&u8_StringSend[u8_counter],&u8_UnUsedReceived);
	while(u8_StringSend[u8_counter] != '\0' && u8_counter !=254)
	{
		u8_counter ++;
		MCAL_SPISlaveTXRX(&u8_StringSend[u8_counter],&u8_UnUsedReceived);
		
	}
	
	
}
void MCAL_SPISlaveReceive_String(uint8_t *u8_StringReceive)
{
	/* counter for the string */
	uint8_t u8_counter=0;
	
	/* it only receive so neglect the data send */
	uint8_t u8_NotUsedSend;
	/* start receiving data */
	MCAL_SPISlaveTXRX(&u8_NotUsedSend,&u8_StringReceive[u8_counter]);
	
	/* till the end of the string */
	while(u8_StringReceive[u8_counter] != '\0')
	{
		u8_counter++;
		MCAL_SPISlaveTXRX(&u8_NotUsedSend,&u8_StringReceive[u8_counter]);
		
	}
	
}
void MCAL_SPI_EnableInterrupts(void)
{
	
	
	
	/* Enable global interrupt */
	SREG |=(1<<7);
	/*Enable SPIE */
	SPCR |=(1<<SPCR_SPIE);
}
void MCAL_SPI_DisableInterrupt(void)
{
	/*Disable SPIE */
	SPCR &=~(1<<SPCR_SPIE);
}
void MCAL_SPISlaveINTDriven(void (*ptr)(void))
{
	/* Enable SPI */
	SPCR |=(1<<SPCR_SPE);
	
	
	/*Enable Interrupts */
	MCAL_SPI_EnableInterrupts();
	
	pCallBack = ptr;
	
}
void MCAL_SPISlaveTrans(uint8_t DataTrans)
{
	volatile char flush_buffer;
	/* load data to be send into SPI data reg */
	SPDR = DataTrans;
	
	/* wait until flag is set */
	while(!(SPSR &(1<<SPSR_SPIF)));
	
	flush_buffer = SPDR;
	
}
void MCAL_SPIMasterReceive(uint8_t *ReceivedData)
{
	
	/* apply low signal to SS*/
	PORTB &=~(1<<PB_SS);
	
	/* load data to be send into SPI data reg */
	SPDR = 0xff;
	
	
	/* wait until flag is set */
	while(!(SPSR &(1<<SPSR_SPIF)));
	
	
	/* received Data   */
	*ReceivedData = SPDR;
	
	/* reset SS to High */
	//PORTB |=(1<<PB_SS);
}

void __vector_12(void)
{
	SPDR = TransSPDR_Value ;
	
	
	
	pCallBack();
}