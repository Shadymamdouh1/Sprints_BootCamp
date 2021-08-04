/*
 * Dio.c
 *
 * Created: 7/14/2021 11:53:26 AM
 *  Author: Shady Mamdouh
 */ 
#include "register.h"
#include "types.h"
#include "DIO.h"

enuDio_Status_t Dio_init(strDio_Config_t* strDio_pins)
{
	
	
   switch(strDio_pins->u8_PortNum)
   {
   case PORT_A :
			{
				if(strDio_pins->u8_Direction==DIO_PIN_DIR_INPUT)
				{
					DDRA &=~(1<< (strDio_pins->u8_PinNum));
					
				}
				else if (strDio_pins->u8_Direction==DIO_PIN_DIR_OUTPUT)
				{
					DDRA |=(1<<(strDio_pins->u8_PinNum));
				}
				if(strDio_pins->u8_InitState==0)
				{
					PORTA &=~(1<< (strDio_pins->u8_PinNum));
					
				}
				else if (strDio_pins->u8_InitState==1)
				{
					PORTA |=(1<<(strDio_pins->u8_PinNum));
				}
	
				
				break;
			}
	case PORT_B :
	    {
		     if(strDio_pins->u8_Direction==DIO_PIN_DIR_INPUT)
		     {
	        		DDRB &=~(1<< (strDio_pins->u8_PinNum));
			
		     }
		    else if (strDio_pins->u8_Direction==DIO_PIN_DIR_OUTPUT)
		    {
			DDRB |=(1<<(strDio_pins->u8_PinNum));
		    }
			if(strDio_pins->u8_InitState==0)
			{
				PORTB &=~(1<< (strDio_pins->u8_PinNum));
				
			}
			else if (strDio_pins->u8_InitState==1)
			{
				PORTB |=(1<<(strDio_pins->u8_PinNum));
			}
		        break;
	     }
	case PORT_C :
	{
		if(strDio_pins->u8_Direction==DIO_PIN_DIR_INPUT)
		{
			DDRC &=~(1<< (strDio_pins->u8_PinNum));
			
		}
		else if (strDio_pins->u8_Direction==DIO_PIN_DIR_OUTPUT)
		{
			DDRC |=(1<<(strDio_pins->u8_PinNum));
		}
		if(strDio_pins->u8_InitState==0)
		{
			PORTC &=~(1<< (strDio_pins->u8_PinNum));
			
		}
		else if (strDio_pins->u8_InitState==1)
		{
			PORTC |=(1<<(strDio_pins->u8_PinNum));
		}
		        break;
	    }
		
		case PORT_D :
		{
			if(strDio_pins->u8_Direction==DIO_PIN_DIR_INPUT)
			{
				DDRD &=~(1<< (strDio_pins->u8_PinNum));
				
			}
			else if (strDio_pins->u8_Direction==DIO_PIN_DIR_OUTPUT)
			{
				DDRD |=(1<<(strDio_pins->u8_PinNum));
			}
			if(strDio_pins->u8_InitState==0)
			{
				PORTD &=~(1<< (strDio_pins->u8_PinNum));
				
			}
			else if (strDio_pins->u8_InitState==1)
			{
				PORTD |=(1<<(strDio_pins->u8_PinNum));
			}
			break;
		}			
   }
   
   return DIO_STATUS_ERROR_OK;
}
enuDio_Status_t Dio_readPin(uint8_t u8_port,uint8_t u8_pinID, uint8_t *pu8_pinValue)
{
switch(u8_port)
{
	case PORT_A :
	{
		
		*pu8_pinValue = ((PINA & (1<<u8_pinID) ) >> u8_pinID);
		break;
	}
	case PORT_B :
	{
		*pu8_pinValue = ((PINB & (1<<u8_pinID) ) >> u8_pinID);
		break;
	}
	case PORT_C :
	{
		*pu8_pinValue = ((PINC & (1<<u8_pinID) ) >> u8_pinID);
		break;
	}
	case PORT_D :
	{
		*pu8_pinValue = ((PIND & (1<<u8_pinID) ) >> u8_pinID);
		break;
	}
}
}
enuDio_Status_t Dio_writePin(uint8_t u8_Port ,uint8_t u8_pinID, uint8_t pu8_pinValue)
{
	
	switch(u8_Port)
	{
		case PORT_A :
		{
			if(pu8_pinValue ==0)
			{
				PORTA &=~(1<<u8_pinID);
				return DIO_STATUS_ERROR_OK;
			}
			else if(pu8_pinValue ==1)
			{
				PORTA |=(1<<u8_pinID);
				return DIO_STATUS_ERROR_OK;
			}
			
			break;
		}
		case PORT_B :
		{
			if(pu8_pinValue ==0)
			{
				PORTB &=~(1<<u8_pinID);
				break;
			}
			else if(pu8_pinValue ==1)
			{
				PORTB |=(1<<u8_pinID);
				
				break;
			}
		}
		case  PORT_C :
		{
			if(pu8_pinValue ==0)
			{
				PORTC &=~(1<<u8_pinID);
				break;
			}
			else if(pu8_pinValue ==1)
			{
				PORTC |=(1<<u8_pinID);
				break;
			}
		}
		case  PORT_D :
		{
			if(pu8_pinValue ==0)
			{
				PORTD &=~(1<<u8_pinID);
				break;
			}
			else if(pu8_pinValue ==1)
			{
				PORTD |=(1<<u8_pinID);
				break;
			}
			break;
		}	
}
	
	
}
enuDio_Status_t Dio_togglePin(uint8_t u8_Port,uint8_t u8_pinID)
{  
	switch(u8_Port)
	{
		case PORT_A : 
		{
			
			PORTA ^=(1<<u8_pinID);
			break;
		}
		case PORT_B : 
		{
			PORTB ^=(1<<u8_pinID);
			break;
		}
		case PORT_C :
		{
			PORTC ^=(1<<u8_pinID);
			break;
		}
		case PORT_D :
		{
			PORTD ^=(1<<u8_pinID);
			break;
		}
	}
	
}
void Dio_SetPinDirection(uint8_t u8_Port, uint8_t  u8_PIN_num, uint8_t u8_Direction)
{
	switch(u8_Port)
	{
		case PORT_A :
		{
			if (u8_Direction==DIO_PIN_DIR_INPUT)
			{
				DDRA &=~(1<<u8_PIN_num);
			}
			else
			{
				DDRA |=(1<<u8_PIN_num);
			}
			break;
		}
		case PORT_B :
		{
			if (u8_Direction==DIO_PIN_DIR_INPUT)
			{
				DDRB &=~(1<<u8_PIN_num);
			}
			else
			{
				DDRB |=(1<<u8_PIN_num);
			}
			break;
		}
		case PORT_C :
		{
			if (u8_Direction==DIO_PIN_DIR_INPUT)
			{
				DDRC &=~(1<<u8_PIN_num);
			}
			else
			{
				DDRC |=(1<<u8_PIN_num);
			}
			break;
		}
		case PORT_D :
		{
			if (u8_Direction==DIO_PIN_DIR_INPUT)
			{
				DDRD &=~(1<<u8_PIN_num);
			}
			else
			{
				DDRD |=(1<<u8_PIN_num);
			}
			break;
		}
		
	}
}
void DIO_SetPortDirection(uint8_t u8_port , uint8_t u8_Direction)
{
	switch(u8_port)
	{
		case PORT_A :
		{
			if (u8_Direction==DIO_PIN_DIR_INPUT)
			{
				DDRA =0;
				break;
			}
			else
			{
				DDRA =0xFF;
				break;
			}
			
		}
		case PORT_B :
		{
			if (u8_Direction==DIO_PIN_DIR_INPUT)
			{
				DDRB =0;
				break;
			}
			else
			{
				DDRB =0xFF;
				break;
			}
		}
		case PORT_C :
		{
			if (u8_Direction==DIO_PIN_DIR_INPUT)
			{
				DDRC =0;
				break;
			}
			else
			{
				DDRC =0xFF;
				break;
			}
		}
		case PORT_D :
		{
			if (u8_Direction==DIO_PIN_DIR_INPUT)
			{
				DDRD =0;
				break;
			}
			else
			{
				DDRD =0xFF;
				break;
			}
		}
	}
}
void DIO_WritePort(uint8_t u8_port , uint8_t u8_val )
{
	switch(u8_port)
	{
		case PORT_A :
		{
			PORTA = u8_val ;
			break;
		}
		case  PORT_B :
		{
			PORTB = u8_val;
		}
		case PORT_C :
		{
			PORTC = u8_val;
			break;
		}
		case PORT_D :
		{
			PORTD = u8_val;
			break;
		}
	}
}