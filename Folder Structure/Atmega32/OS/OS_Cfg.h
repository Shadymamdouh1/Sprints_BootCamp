/*****************************************************************************
* Module: OS Module
* File Name: OS.h
* Description: Header file for configuration the operating system
* Author: Shady Mamdouh
* Date: 8/28/2021
******************************************************************************/


#ifndef OS_CFG_H_
#define OS_CFG_H_





typedef struct OS_Config_t
{
  uint8_t	SysTickChannel;
  uint8_t   CPULoadTimerCH ;
  uint32_t   SystickValue;   /* in msec*/
  
	
}OS_Config_t;
#define Channel0   0U
#define Channel1   1U
#define Channel2   2U

#define MAX_ALLOWED_TASKS  10
#define  MAX_PRIORITY_NUM	   10


#define SysTickmsec   5UL
#define CPULoadFramecal 100UL
#define SamplePerFrame  5UL

#endif /* OS_CFG_H_ */