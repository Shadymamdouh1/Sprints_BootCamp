/*****************************************************************************
* Module: Button Module
* File Name: buttonDebounceHandler_Cfg.c
* Description: Source file for Button Debounce Handler Cfg Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "buttonDebounceHandler.h"

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/* here you adjust the buttons configurations */
strButtonDebounce_Config_t strButtonDeounce_Config[DEBOUNCE_BUTTONS_USED]=
{
	 /*Button Id */	  /* timer Id */     /* delay Ticks */  /* delay type */		/* change check type */
	{D_BUTTON_1_ID, D_BUTTON_1_TIMER_ID,  D_BUTTON_1_DELAY,	  DELAY_TIMER_ASYNC,		POLLING },
	{D_BUTTON_2_ID, D_BUTTON_2_TIMER_ID,  D_BUTTON_2_DELAY,	  DELAY_TIMER_ASYNC,		POLLING }
	
};