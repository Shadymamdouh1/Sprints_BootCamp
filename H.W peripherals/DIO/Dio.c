/*
 * Dio.c
 *
 * Created: 7/14/2021 11:53:26 AM
 *  Author: Shady Mamdouh
 */ 
#include "register.h"
#include "types.h"
#include "Dio.h"

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
				else if (strDio_pins->u8_Direction==1)
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
			else if (strDio_pins->u8_Direction==1)
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
		else if (strDio_pins->u8_Direction==1)
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
			else if (strDio_pins->u8_Direction==1)
			{
				PORTD |=(1<<(strDio_pins->u8_PinNum));
			}
			break;
		}			
   }
   
   return DIO_STATUS_ERROR_OK;
}
enuDio_Status_t Dio_readPin(uint8_t u8_pinID, uint8_t *pu8_pinValue)
{
	
// Guard
/*if(pu8_pinValue==NULL)	
{
return DIO_STATUS_ERROR_NOK;
}*/
if(u8_pinID >=0 && u8_pinID < 8)
{
	*pu8_pinValue = ((PINA & (1<<u8_pinID) ) >> u8_pinID);
	return DIO_STATUS_ERROR_OK;
}
if(u8_pinID >=8 && u8_pinID <16)
{    
	u8_pinID -=8;
	*pu8_pinValue = ((PINB & (1<<u8_pinID) ) >> u8_pinID);
	return DIO_STATUS_ERROR_OK;
}
if(u8_pinID >=16 && u8_pinID <24)
{
	u8_pinID -=16;
	*pu8_pinValue = ((PINC & (1<<u8_pinID) ) >> u8_pinID);
	return DIO_STATUS_ERROR_OK;
}
if(u8_pinID >=24 && u8_pinID <32)
{
	u8_pinID -=24;
	*pu8_pinValue = ((PIND & (1<<u8_pinID) ) >> u8_pinID);
	return DIO_STATUS_ERROR_OK;
}
else
{
  return DIO_STATUS_ERROR_NOK;
}
}
enuDio_Status_t Dio_writePin(uint8_t u8_pinID, uint8_t pu8_pinValue)
{
	//port A
if(u8_pinID >=0 && u8_pinID < 8)
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
	else
	{   
		// value not 1 or 0
		return DIO_STATUS_ERROR_NOK;
	}
	
}
 // port B
if(u8_pinID >=8 && u8_pinID <16)
{
	u8_pinID -=8;
	if(pu8_pinValue ==0)
	{
		PORTB &=~(1<<u8_pinID);
		return DIO_STATUS_ERROR_OK;
	}
	else if(pu8_pinValue ==1)
	{
		PORTB |=(1<<u8_pinID);
		return DIO_STATUS_ERROR_OK;
	}
	else
	{
		// value not 1 or 0
		return DIO_STATUS_ERROR_NOK;
	}
	
	
	
}
// PORT C
if(u8_pinID >=16 && u8_pinID <24)
{
	u8_pinID -=16;
	if(pu8_pinValue ==0)
	{
		PORTC &=~(1<<u8_pinID);
		return DIO_STATUS_ERROR_OK;
	}
	else if(pu8_pinValue ==1)
	{
		PORTC |=(1<<u8_pinID);
		return DIO_STATUS_ERROR_OK;
	}
	else
	{
		// value not 1 or 0
		return DIO_STATUS_ERROR_NOK;
	}
	
	
}
// port D
if(u8_pinID >=24 && u8_pinID <32)
{
	u8_pinID -=24;
	if(pu8_pinValue ==0)
	{
		PORTD &=~(1<<u8_pinID);
		return DIO_STATUS_ERROR_OK;
	}
	else if(pu8_pinValue ==1)
	{
		PORTD |=(1<<u8_pinID);
		return DIO_STATUS_ERROR_OK;
	}
	else
	{
		// value not 1 or 0
		return DIO_STATUS_ERROR_NOK;
	}
	
	
}

	return DIO_STATUS_ERROR_NOK;

}
enuDio_Status_t Dio_togglePin(uint8_t u8_pinID)
{   
	//PORT A
   if(u8_pinID >=0 && u8_pinID < 8)
   {
   
   PORTA ^=(1<<u8_pinID);
   return DIO_STATUS_ERROR_OK;
   }
   //PORT B
   if(u8_pinID >=8 && u8_pinID <16)
   {
	   u8_pinID -=8;
	   PORTA ^=(1<<u8_pinID);
	   return DIO_STATUS_ERROR_OK;
   }
   // PORT C
   if(u8_pinID >=16 && u8_pinID <24)
   {
	   u8_pinID -=16;
	   PORTA ^=(1<<u8_pinID);
	   return DIO_STATUS_ERROR_OK;
	   
   }
   // port D
   if(u8_pinID >=24 && u8_pinID <32)
   {
	   u8_pinID -=24;
	   PORTA ^=(1<<u8_pinID);
	   return DIO_STATUS_ERROR_OK;
	   
   }
   
   return DIO_STATUS_ERROR_NOK;
}