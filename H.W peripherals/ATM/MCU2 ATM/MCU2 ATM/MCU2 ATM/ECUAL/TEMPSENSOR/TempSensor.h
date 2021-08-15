/*
 * TempSensor.h
 *
 * Created: 8/3/2021 8:05:50 PM
 *  Author: Shady Mmadouh
 */ 


#ifndef TEMPSENSOR_H_
#define TEMPSENSOR_H_
#include "types.h"
void TempSensorInit(uint8_t u8_channelID, uint8_t u8_Vref);
void TempSensorGetTemp(uint8_t *pu8_TEMP);


#endif /* TEMPSENSOR_H_ */