/*
 * Dio_Cfg.c
 *
 * Created: 7/14/2021 11:55:22 AM
 *  Author: Shady mamdouh 
 */ 
#include "Dio_Cfg.h"
#include "Dio.h"

// array of pin structure 

strDio_Config_t strDio_pins[DIO_USED_PINS_NUM]=
{
	{PORT_A,PIN_0,DIO_PIN_DIR_INPUT,0},
	{PORT_A,PIN_1,DIO_PIN_DIR_INPUT,0},
	{PORT_A,PIN_2,DIO_PIN_DIR_INPUT,0}
};