/*
 * app.h
 *
 * Created: 7/25/2021 1:23:12 PM
 *  Author: Shady Mamdouh 
 */ 


#ifndef APP_H_
#define APP_H_
/*************************************************
				APIs
*************************************************
* Name : APPInit
* Description : initialize the UART & SPI according to config files
*/
void APPInit(void);
/*****************************************************************
* Name : APPGetString
* Description : get string from the Master using SPI
*/
void APPGetString(void);
/*****************************************************************
* Name : APP_transmit
* Description : transmit the string to the terminal over UART
*/
void APP_transmit(void);
/***************************************************************/
#endif /* APP_H_ */