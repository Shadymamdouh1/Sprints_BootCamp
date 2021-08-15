/*
 * TemPsensor.c
 *
 * Created: 8/3/2021 8:05:28 PM
 *  Author: Shady Mamdouh 
 */ 
#include "types.h"
#include "..\..\MCAL\ADC\ADC.h"
#include "..\..\MCAL\DIO\DIO.h"
#include "TempSensor.h"
/*********************************************************/
 /* will affect temp calculations */
 
uint8_t gu8_Vref;
/******************************************************/
void TempSensorInit(uint8_t u8_channelID, uint8_t u8_Vref)
{
	/* initialize the ADC */
	ADC_CONFIG_STRUCT.Channels =u8_channelID;
	ADC_CONFIG_STRUCT.Clock_selector=clk_128;
	ADC_CONFIG_STRUCT.Vref_selector=AVCC_with_extCapacitor;
	ADC_init(ADC_CONFIG_STRUCT);
	
	gu8_Vref = u8_Vref;
	
	if (u8_channelID==0)
	{
		strDio_pins.u8_PortNum =PORT_A;
		strDio_pins.u8_PinNum =PIN_0;
		strDio_pins.u8_Direction=DIO_PIN_DIR_INPUT;
		Dio_init(&strDio_pins);
	}
	
}
void TempSensorGetTemp(uint8_t *pu8_TEMP)
{
	strDio_pins.u8_PortNum =PORT_A;
	strDio_pins.u8_PinNum =PIN_0;
	strDio_pins.u8_Direction=DIO_PIN_DIR_INPUT;
	Dio_init(&strDio_pins);
	
	uint16_t u16_Sample;
	ADC_GetSingleSample(&u16_Sample);
	
	/* temp equation according to LM35 sensor */
	
	*pu8_TEMP =(u16_Sample /((.01*RESOLUTION_LEVELS)/gu8_Vref));
}