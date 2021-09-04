/*****************************************************************************
* Module: Button Module
* File Name: buttonDebounceHandler.c
* Description: Source file for Button Debounce Handler Module
* Author: Mohamed Magdy
* Date: 21-July-2021
******************************************************************************/

/*- INCLUDES
----------------------------------------------*/
#include "buttonDebounceHandler.h"

/* handler states */
#define DEBOUNCE_HANDLER_IDLE									(90U)
#define DEBOUNCE_HANDLER_EVENT_RECV					        	(91U)
#define DEBOUNCE_HANDLER_EVENT_WAITING						    (92U)
#define DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE				(93U)
/*- GLOBAL EXTERN VARIABLES -------------------------------------*/
uint8_t au8_buttonLegitState[DEBOUNCE_BUTTONS_USED] =
{
	BUTTON_STATE_RELEASED,
	BUTTON_STATE_RELEASED
};

uint8_t au8_buttonCurrentState[DEBOUNCE_BUTTONS_USED] = 
{
	BUTTON_STATE_RELEASED,
	BUTTON_STATE_RELEASED
};

uint8_t au8_debouncingHandlerState[DEBOUNCE_BUTTONS_USED] =
{
	DEBOUNCE_HANDLER_IDLE,
	DEBOUNCE_HANDLER_IDLE
};

/* you must put all buttons with same arrange as cfg struct, if not using timer Async, put it as default callBack */
callBackFun_t buttonTimerCallBackFun[DEBOUNCE_BUTTONS_USED] = 
{
	callBack_Button_1,
	callBack_Button_2
};

// callBackFun_t buttonExtIntCallBackFun[DEBOUNCE_BUTTONS_USED] =
// {
// 	eventReceived_Button1_CallBack,
// 	eventReceived_Button2_CallBack
// };

/*- LOCAL FUNCTIONS IMPLEMENTATION
------------------------*/
/************************************************************************************
* Parameters (in): None
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: update state of a given button.
************************************************************************************/
Std_ReturnType debounceHandler_updateButtonState(uint8_t debouncingButtonId)
{
	switch(au8_debouncingHandlerState[debouncingButtonId])
	{
		case(DEBOUNCE_HANDLER_IDLE):
		{
			/* check if button is polling */
			if(strButtonDeounce_Config[debouncingButtonId].u8_buttonCheck_PollingOrExtInt == POLLING)
			{
				Button_getState(strButtonDeounce_Config[debouncingButtonId].u8_buttonId,
				&au8_buttonCurrentState[debouncingButtonId]);
				
				if(au8_buttonCurrentState[debouncingButtonId] != au8_buttonLegitState[debouncingButtonId])
				{
					au8_debouncingHandlerState[debouncingButtonId] = DEBOUNCE_HANDLER_EVENT_RECV; 
				}
				else
				{
					/* not pressed yet */
				}
			}
			else
			{
				/* ext int will trigger */
			}			
			break;
		}
		case(DEBOUNCE_HANDLER_EVENT_RECV):
		{
			/* start delay timer */
			if(strButtonDeounce_Config[debouncingButtonId].u8_delayType == DELAY_TIMER_ASYNC)
			{
				GptStart_aSync(strButtonDeounce_Config[debouncingButtonId].u8_timerId,
				strButtonDeounce_Config[debouncingButtonId].u16_delayTicks,
				buttonTimerCallBackFun[debouncingButtonId]);
				
				au8_debouncingHandlerState[debouncingButtonId] = DEBOUNCE_HANDLER_EVENT_WAITING;				
			}
			else if(strButtonDeounce_Config[debouncingButtonId].u8_delayType == DELAY_TIMER_SYNC)
			{
				GptStart_Sync(strButtonDeounce_Config[debouncingButtonId].u8_timerId,
				strButtonDeounce_Config[debouncingButtonId].u16_delayTicks);	
				
				/* change state */
				au8_debouncingHandlerState[debouncingButtonId] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;			
			}
			else if(strButtonDeounce_Config[debouncingButtonId].u8_delayType == DELAY_LOOP)
			{
				/* manual delay_ms 20 */
				Delay_ms(20);
				/* change state */
				au8_debouncingHandlerState[debouncingButtonId] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;	
			}
			else
			{
				
			}
			break;
		}
		case(DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE):
		{
			Button_getState(strButtonDeounce_Config[debouncingButtonId].u8_buttonId, 
							&au8_buttonCurrentState[debouncingButtonId]);
			
			if(au8_buttonCurrentState[debouncingButtonId] != au8_buttonLegitState[debouncingButtonId])
			{ 
				 /* a new legit change in button */
				au8_buttonLegitState[debouncingButtonId] = au8_buttonCurrentState[debouncingButtonId];
				
				break;
			}
			else
			{
				/* fake change */
			}
			/* make state idle again */
			au8_debouncingHandlerState[debouncingButtonId] = DEBOUNCE_HANDLER_IDLE;            
			break;
		}
		case(DEBOUNCE_HANDLER_EVENT_WAITING):
		{
			/* busy */
			break;
		}						
		default:
		{
			return E_NOT_OK;
		}
	}
	return E_OK;
}
/************************************************************************************
* Parameters (in): Button ID and pointer to variable to hold the state
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: gets the state of a given button pressed or released
************************************************************************************/
Std_ReturnType debounceHandler_getButtonState(uint8_t debouncingButtonId, uint8_t* debouncingButtonState)
{
	/* return current legit state of given button pressed or not */
	*debouncingButtonState = au8_buttonLegitState[debouncingButtonId];
	return E_OK;
}

/************************************************************************************
* Parameters (in): Button ID and pointer to variable to hold the state
* Parameters (out): Error Status
* Return value: Std_ReturnType
* Description: gets the state of a given button pressed or released
************************************************************************************/
Std_ReturnType debounceHandler_eventReceived(uint8_t debouncingButtonId)
{
	if(au8_debouncingHandlerState[debouncingButtonId] != DEBOUNCE_HANDLER_IDLE)
	{
		return E_NOT_OK;
	}
	else
	{
		/* start timer delay flag */
		au8_debouncingHandlerState[debouncingButtonId] = DEBOUNCE_HANDLER_EVENT_RECV; 
	}
	return E_OK;
}
















/* Event Trigger Call Back Functions for External Int */
void eventReceived_Button1_CallBack(void)
{
	debounceHandler_eventReceived(DEB_BUTTON_1_ID);
}

void eventReceived_Button2_CallBack(void)
{
	debounceHandler_eventReceived(DEB_BUTTON_2_ID);
}


/* Timers Call Back Functions */
void callBack_Button_1(void)
{
	au8_debouncingHandlerState[DEB_BUTTON_1_ID] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;
	
}

void callBack_Button_2(void)
{
	au8_debouncingHandlerState[DEB_BUTTON_2_ID] = DEBOUNCE_HANDLER_DELAY_ENDED_UPDATING_STATE;
	
}

void callBack_Button_Default(void)
{
	/* does nothing */
}