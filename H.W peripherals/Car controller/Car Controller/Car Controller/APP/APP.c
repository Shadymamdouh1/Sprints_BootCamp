/*/****************************************
 * APP.c
 *
 * Created: 7/16/2021 9:05:30 PM
 *  Author: Shady Mamdouh 
 ***************************************/
/******************INCLUDES*****************/
#include "types.h"
#include "..\ECUAL\Button\Button.h"
#include "..\ECUAL\Motor\Motor.h"
#include "APP.h"
#include "register.h"
/******************************************/

/***************Global variables**********/
uint8_t Current_GearState =  InitialState ;
/****************************************/


/******************************************************
*					    APIs                          *
*******************************************************/

/***************** Initialization*********************/

void App_init(void)
{
	
	Button_init();
	Motor_init();
	
}
/*******************************************************/

/********************************************************/
void GetState(void)
{   
	uint8_t u8_State;
	// update GearButton state
	Button_updateState(GearButton);
	Button_getState(GearButton,&u8_State);
	
	
	// to avoid multi pressing 
	if(u8_State==BUTTON_STATE_PRESSED)
	{
		
		while(u8_State==BUTTON_STATE_PRESSED)
		{
			Button_updateState(GearButton);
			Button_getState(GearButton,&u8_State);
			
		}
	// update gear current state according to previous state
		switch(Current_GearState)
		{
			case InitialState :
			{    
				Current_GearState =GearForward_30;
				break;
			}
			case GearForward_30 :
			{
				Current_GearState=GearForward_50;
				break;
			}
			case GearForward_50 :
			{
				Current_GearState =GearForward_90;
				break;
			}
			case GearForward_90 :
			{
				Current_GearState= GearBackForward_30;
				break;
			}
			case GearBackForward_30 :
			{
				Current_GearState =GearForward_30;
				break;
			}
		}
		
	}

}
/**********************************************************************/

void updateAPPState(void)
{
	
	uint8_t u8_State;
//*************************** move button check*************************
	Button_updateState(MoveButton);
	Button_getState(MoveButton,&u8_State);
	if(u8_State==BUTTON_STATE_PRESSED)
	{
		MoveForward(Current_GearState);
		while(u8_State==BUTTON_STATE_PRESSED)
		{
			
			Button_updateState(MoveButton);
			Button_getState(MoveButton,&u8_State);
			
		}
		Stop();
	}
/**************************CHeck right Button********************************/	
	Button_updateState(RightButton);
	Button_getState(RightButton,&u8_State);
	if(u8_State==BUTTON_STATE_PRESSED)
	{
		MoveRight(Current_GearState);
		while(u8_State==BUTTON_STATE_PRESSED)
		{
			
			Button_updateState(RightButton);
			Button_getState(RightButton,&u8_State);
			
		}
		Stop();
	}
/**************************CHeck Left Button********************************/
Button_updateState(LeftButton);
Button_getState(LeftButton,&u8_State);
if(u8_State==BUTTON_STATE_PRESSED)
{
	MoveLeft(Current_GearState);
	while(u8_State==BUTTON_STATE_PRESSED)
	{
		
		Button_updateState(LeftButton);
		Button_getState(LeftButton,&u8_State);
		
	}
	Stop();
}	
	
	}

/***************************************************************/
void MoveForward(uint8_t Gear_state)
{   
	switch(Gear_state)
	{
		case InitialState :
		{
			break;
		}
		case GearForward_30 :
		{
			Motor_moveForward(RightMotorID,30);
			Motor_moveForward(LeftMotorID,30);
			break;
		}
		case GearForward_50 :
		{
			Motor_moveForward(RightMotorID,50);
			Motor_moveForward(LeftMotorID,50);
			break;
		
		}
		case GearForward_90 :
		{
			Motor_moveForward(RightMotorID,90);
			Motor_moveForward(LeftMotorID,90);
			break;
		}
		case GearBackForward_30 :
		{
			MoveBack();
			break;
		}
		
	}
	
}
/***********************************************************/
void MoveBack(void)
{
	Motor_moveBackward(RightMotorID,30);
	Motor_moveBackward(LeftMotorID,30);
}

/***********************************************************/
void MoveRight(uint8_t Gear_state)
{   
	switch(Gear_state)
	{
		case InitialState :
		{
			break;
		}
		case GearForward_30 :
		{
			// stop the right motor
			Motor_stop(RightMotorID);
			//run the left motor
			Motor_moveForward(LeftMotorID,30);
			
			break;
		}
		case GearForward_50 :
		{
			// stop the right motor
			Motor_stop(RightMotorID);
			//run the left motor
			Motor_moveForward(LeftMotorID,30);
			break;
			
		}
		case GearForward_90 :
		{
			// stop the right motor
			Motor_stop(RightMotorID);
			//run the left motor
			Motor_moveForward(LeftMotorID,30);
			break;
		}
		case GearBackForward_30 :
		{
			// stop the right motor
			Motor_stop(RightMotorID);
			//run the left motor
			Motor_moveForward(LeftMotorID,30);
			break;
		}
		
	}
		
}
/****************************************************************/
void MoveLeft(uint8_t Gear_state)
{
	
	switch(Gear_state)
	{
		case InitialState :
		{
			break;
		}
		case GearForward_30 :
		{
			// stop the left motor
			Motor_stop(LeftMotorID);
			//run the right motor
			Motor_moveForward(RightMotorID,30);
			
			break;
		}
		case GearForward_50 :
		{
			// stop the left motor
			Motor_stop(LeftMotorID);
			//run the right motor
			Motor_moveForward(RightMotorID,30);
			break;
			
		}
		case GearForward_90 :
		{
			// stop the left motor
			Motor_stop(LeftMotorID);
			//run the right motor
			Motor_moveForward(RightMotorID,30);
			break;
		}
		case GearBackForward_30 :
		{
			// stop the left motor
			Motor_stop(LeftMotorID);
			//run the right motor
			Motor_moveForward(RightMotorID,30);
			break;
		}
		
	}
	
}
/***************************************************************/
void Stop(void)
{
	Motor_stop(LeftMotorID);
	Motor_stop(RightMotorID);
}
/************************************************************/