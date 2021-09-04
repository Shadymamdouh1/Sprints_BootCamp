/*****************************************************************************
* Module: Button Module
* File Name: Button_Cfg.h
* Description: Header file for Button Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/


#ifndef BUTTON_CFG_H_
#define BUTTON_CFG_H_


/*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*-*/
/*-*-*-*-*- CONSTANTS -*-*-*-*-*-*/

/* user set the number of pins used in the project */

#define BUTTONS_USED			(2U)

/* buttons dio ID */
#define BUTTON_1_DIO_ID	         PORTD_PIN2_ID	
#define BUTTON_2_DIO_ID	         PORTA_PIN0_ID

/* button Id according to cfg struct array order */
#define BUTTON_1_ID				(0U)
#define BUTTON_2_ID				(1U)

/* button pull up or down ? */	
#define PULL_UP					(99U)
#define PULL_DOWN				(98U)

#endif /* BUTTON_CFG_H_ */