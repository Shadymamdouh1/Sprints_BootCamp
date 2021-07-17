/*
 * SW_PWM.h
 *
 * Created: 7/15/2021 3:32:14 PM
 *  Author: Shady mamdouh 
 */ 


#ifndef SW_PWM_H_
#define SW_PWM_H_
//**************MACROS*******************************/
#define TIMER_CH_0  0
#define PWM_CH_0    0
#define TIMER_CH_1  1
#define PWM_CH_1    1
/********************Enums****************************/

/********************Error handling******************/
typedef enum
{
	SWPWM_STATUS_ERROR_NOK,
	SWPWM_STATUS_ERROR_OK,
	SWPWM_STATUS_NOT_INIT,
	SWPWM_STATUS_PWM_ID_INVALID,
	SWPWM_STATUS_DC_OUTRANGE
}enuSWPwm_Status_t;

//******** Data Type for the PWM Channel Configuration for pin and timer channel****************************/

typedef struct
{
uint8_t u8_DioChannelID;
uint8_t u8_GptChannelID;
}strSWPwm_ChannelConfig_t;

/***************** Data for wave form function*****************************/
typedef struct
{
	uint32_t Ticks_ON;
	uint32_t Ticks_OFF ;
	uint8_t prevoius;
}strSWPwm_ChannelData_t;
// Global var of waveform Data
strSWPwm_ChannelData_t channel0_data;
/********************************************************************/

/**********************  APIs   ****************************************/

/**********************************************************************
	Name : SWPwm_Init
	Description : this function used to initialize the selected channel pins and the timer channel that 
	will be used to generate SW PWM it has an access on lower layer modules TIMER and Dio 

*/
enuSWPwm_Status_t SWPwm_Init(void); 
/*************************************************************************/

/*******************************************************************************************
Name : SWPwm_Start
Description: - this function takes a structure contains data about the selected pin and timer
			 - this data is assigned in its index in an array of structure allocated at 
			    SW_Cfg.c
			 - it also takes the frequency to represent the time period of the PWM wave 
			 - it takes the duty cycle that represents the Ton 
			 - it enables Global interrupt and works by interrupt and call back mechanism
			 -[NOTE] : this function calculations depends on choosing MC frequency of 1MHz and timer  pre-scaler of /64
			 to be suitable for our application motor operation frequency
			  
*/
enuSWPwm_Status_t SWPwm_Start(strSWPwm_ChannelConfig_t u8_ChannelID, uint32_t u32_Freq, uint8_t u8_DutyCycle);
/********************************************************************************************************/


/********************************************************************************************************
Name : SWPwm_Start
Description: this function is used to disable PWM on a specific Channel
		   : it also disable the interrupt related to the chosen timer channel 
*/
enuSWPwm_Status_t SWPwm_Stop(strSWPwm_ChannelConfig_t u8_ChannelID);
/********************************************************************************************************/




#endif /* SW_PWM_H_ */