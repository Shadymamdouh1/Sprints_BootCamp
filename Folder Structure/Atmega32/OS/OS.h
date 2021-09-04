/*****************************************************************************
* Module: OS Module
* File Name: OS.h
* Description: Header file for the operating system
* Author: Shady Mamdouh
* Date: 8/28/2021
******************************************************************************/


#ifndef OS_H_
#define OS_H_
#include "OS_Cfg.h"

typedef uint8_t taskId_t ;
typedef void(*TaskFunction_t)(void);
/****************************Return values***********************************/
typedef enum OS_ERROR_t
{
	InvalidChannel,
	OS_ERRORExceedMaxTasks,
	OS_InvalidPtr,
	OS_WrongPriority,
	OS_PreUsedTaskId,
	OS_TaskDeleted,
	OS_NotExistTaskId,
	OS_TSuspended,
	OS_TResumed,
	OS_TaskCreated,
	OS_ERROR_OK
	
}OS_ERROR_t;
/*****************************************************************************************************************
												         APIs
******************************************************************************************************************/
OS_ERROR_t OS_Init(void);
OS_ERROR_t OS_CreateTask(uint8_t *TaskId ,TaskFunction_t TaskFunction , uint32_t TaskPeriod , uint8_t TaskPriority  );
OS_ERROR_t OS_DeleteTask(uint8_t TaskId );
void OS_Run(void);
OS_ERROR_t OS_TaskSuspend(taskId_t TaskId);
OS_ERROR_t OS_TaskResume(taskId_t TaskId);


extern OS_Config_t OS_Configuration;
#endif /* OS_H_ */