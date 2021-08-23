/*****************************************************************************
* Module: Button Module
* File Name: buttonDebounceHandler_Cfg.h
* Description: Header file for Button Debounce Handler Cfg Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/

#ifndef BUTTONDEBOUNCEHANDLER_CFG_H_
#define BUTTONDEBOUNCEHANDLER_CFG_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/* user set the number of pins used in the project */

#define DEBOUNCE_BUTTONS_USED			(2U)

/* button Id according to cfg struct array order to be used in function calls */
#define DEB_BUTTON_1_ID				    (0U)
#define DEB_BUTTON_2_ID				    (1U)

/* debounce buttons id to be filled in cfg struct */
#define D_BUTTON_1_ID					BUTTON_1_ID
#define D_BUTTON_2_ID					BUTTON_2_ID

/* timers Id */
#define D_BUTTON_1_TIMER_ID				TIMER_CHANNEL_0_ID
#define D_BUTTON_2_TIMER_ID				TIMER_CHANNEL_1_ID

/* timers delay Ticks */
#define D_BUTTON_1_DELAY				(2500U)
#define D_BUTTON_2_DELAY			    (2500U)

/* delay type */
#define DELAY_TIMER_ASYNC						(50U)
#define DELAY_TIMER_SYNC						(51U)
#define DELAY_LOOP								(52U)

/* event change check type */
#define EXT_INT							(12U)
#define POLLING							(11U)


#endif /* BUTTONDEBOUNCEHANDLER_CFG_H_ */