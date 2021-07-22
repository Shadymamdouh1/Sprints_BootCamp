/*
 * Dio.h
 *
 * Created: 7/14/2021 11:50:23 AM
 *  Author: Shady Mamdouh
 */ 


#ifndef DIO_H_
#define DIO_H_
#include "types.h"
/* File names
Dio.h
Dio.c
Dio_Cfg.h
Dio_Cfg.c
*/

#define PIN_0		0
#define PIN_1		1
#define PIN_2		2
#define PIN_3		3
#define PIN_4		4
#define PIN_5		5
#define PIN_6		6
#define PIN_7		7

#define PORT_A		0
#define PORT_B		1
#define PORT_C		2
#define PORT_D		3

#define PIN_LOW		0U
#define PIN_HIGH	1U

#define PIN_PDR		0U /* Pull Down Resistor */
#define PIN_PUR		1U /* Pull Up Resistor */

typedef enum{
	DIO_STATUS_ERROR_NOK,
	DIO_STATUS_ERROR_OK
}enuDio_Status_t;

typedef enum{
	DIO_PIN_DIR_INPUT,
	DIO_PIN_DIR_OUTPUT
}enuDio_Direction_t;

typedef struct
{
	uint8_t u8_PortNum;
	uint8_t u8_PinNum;
	enuDio_Direction_t u8_Direction;
	uint8_t u8_InitState; /* 1 or 0 for output pin // Pull Down or Pull Up for Input pin*/
}strDio_Config_t;
#define DIO_USED_PINS_NUM 3

/*************************/
/** pinID is the index of the pin structure in the configuration array of structures */

enuDio_Status_t Dio_init(strDio_Config_t* strDio_pins);
enuDio_Status_t Dio_readPin(uint8_t u8_pinID, uint8_t *pu8_pinValue);
enuDio_Status_t Dio_writePin(uint8_t u8_pinID, uint8_t pu8_pinValue);
enuDio_Status_t Dio_togglePin(uint8_t u8_pinID);

/* ToDo *//*
enuDio_Status_t Dio_readPort(uint8_t u8_PortNum, uint8_t *pu8_portValue);
enuDio_Status_t Dio_writePort(uint8_t u8_PortNum, uint8_t u8_portValue);
*//***************/




#endif /* DIO_H_ */