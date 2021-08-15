/*
 * spiConfig.h
 *
 * Created: 7/23/2021 3:22:43 PM
 *  Author: Shady Mamdouh
 */ 


#ifndef SPICONFIG_H_
#define SPICONFIG_H_
/*************first select the operation mode**************************************
* Options : MASTER_MODE
*			SLAVE_MODE
*/
#define OPERATION_MODE MASTER_MODE
/*********************************************************************************/
/*********************** transmission frequency***********************************
* Options : Fosc_4
			Fosc_16
			Fosc_64
			Fosc_128
*/
#define TRANS_FREQ Fosc_128
/**********************************************************************************/
/***********************frequency speed modes***************************************
* Options : NORMAL_SPEED      
			DOUBLE_SPEED     that will duplicate the previous selected frequency
*/
#define FREQ_SPEED NORMAL_SPEED
/**********************************************************************************/

#endif /* SPICONFIG_H_ */