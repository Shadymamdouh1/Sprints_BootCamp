/*****************************************************************************
* Module: OS Module
* File Name: OS.h
* Description: Source file for configuration the operating system
* Author: Shady Mamdouh
* Date: 8/28/2021
******************************************************************************/
#include "..\Microcontroller\Platform_Types.h"
#include "..\Microcontroller\Std_types.h"
#include "OS_Cfg.h"




                              /*sys tick timer*/      /*CPU load timer */   /* systick in msec*/ 
OS_Config_t OS_Configuration = {Channel0     ,           Channel1   ,         SysTickmsec           };                   
                                            