/******************************************************
 * APP.h
 *
 * Created: 7/16/2021 9:05:45 PM
 *  Author: Shady Mamdouh 
 ****************************************************/ 


#ifndef APP_H_
#define APP_H_
#include "types.h"

/***********************Gear States******************************/
typedef enum enGearState_t
{   
	InitialState,
	GearForward_30,
	GearForward_50,
	GearForward_90,
	GearBackForward_30
}strGearState_t;

/******************************************************/


/******************************************************
*					    APIs                          *
*******************************************************/

/***************** Initialization*********************
* Name:   App_init
* Description : initializes App module and 
				lower layer modules  
*
*/
void App_init(void);
/*******************************************************/

/*******************************************************
* Name:   GetState
* Description : used to read the Gear button and update 
*				the Gear state according to the prevoius 
*				gear state
*/				
void GetState(void);
/*******************************************************
* Name: updateAPPState
* Description : used  check if the move 
*				or right or left buttons is pressed
*				then pass the current gear state to
*               movement functions according to button
*/
void updateAPPState(void);
/*******************************************************
* Name: MoveForward
* Description : this function called by updateAPPState  
*               it takes the current gear state to 
*				decide to move or not and speed upon gear state
*/
void MoveForward(uint8_t Gear_state);
/*******************************************************
* Name: MoveBack
* Description : this function called by MoveForward
*               to move back if the current gear state is
*				back_30
*               it has fixed speed 30%
*/				
void MoveBack(void);
/*******************************************************
* Name: MoveRight
* Description : this function called by updateAPPState
*               it takes the current gear state to
*				decide to move right or not and it has fixed speed 30%
*/

void MoveRight(uint8_t Gear_state);
/*******************************************************
* Name: MoveRight
* Description : this function called by updateAPPState
*               it takes the current gear state to
*				decide to move left or not and it has fixed speed 30%
*/

void MoveLeft(uint8_t Gear_state);
/*******************************************************
* Name: MoveRight
* Description : this function represents the stop state
*/
void Stop(void);
/*******************************************************/



#endif /* APP_H_ */