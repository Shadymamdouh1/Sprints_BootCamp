/*
 * APP.h
 *
 * Created: 8/3/2021 7:55:46 PM
 *  Author: Shady Mamdouh
 */ 


#ifndef APP_H_
#define APP_H_

#define TEMP_SENSOR_CHANNEL 0UL
#define TEMP_SENSOR_VREF	5UL

void APP_APPInit(void);
void APP_GetState(void);
void APP_UpdateState(void);

#endif /* APP_H_ */