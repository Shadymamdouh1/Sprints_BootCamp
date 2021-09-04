/*****************************************************************************
* Module: OS Module
* File Name: OS.c
* Description: Source file for the operating system
* Author: Shady Mamdouh
* Date: 8/28/2021
******************************************************************************/
/************************************INCLUDES*************************************/
#include "..\Microcontroller\Platform_Types.h"
#include "..\Microcontroller\Std_types.h"
#include "..\MCAL\Gpt Module\Gpt.h"
#include "..\Patterns\Interrupt Handler\ih_interface.h"
#include "OS_Cfg.h"
#include "OS.h"
#include "..\Microcontroller/Atmega32 Registers/Dio_regs.h"
/********************************************************************************/
#define INITIALIZED				 0U
#define NOT_INITIALIZED			 1U
#define SecTomsec				1000U
#define TaskReady				0U
#define TaskBlocked				1U
#define TaskWaiting				2U
#define TaskSuspended			3U
#define TaskRunning				4U

/*********************************Type Definitions***********************************/

typedef struct TaskData_t
{
	taskId_t TaskID;
	TaskFunction_t TaskFunction;
	uint32_t periodicity ;
	uint8_t  priority;
	uint32_t TaskCounter;
	uint8_t  TaskState;
	
}TaskData_t;
/***************************Global Variables*****************************************/
/*used sys tick timer channel */
uint8_t  gTimerUsedChannel ;
/***********************CPU Load calculations **************************************/
/*used CPU load timer channel */
uint8_t CPULoadTimCh ;
float32_t CPUSleepTime=0;
volatile uint8_t   CPUSleepFlag =0;
/* array to hold CPU load samples per frame */
uint8_t CPUloadSamples[SamplePerFrame];

/*  time per sample */
float32_t SampleTime = (((float32_t) CPULoadFramecal/SamplePerFrame)*SysTickmsec) / SecTomsec;
/*  time per Frame */
//float32_t FrameTime =((float32_t)SampleTime*SamplePerFrame);
/* ticks per sample */
uint32_t SampleTicks = (CPULoadFramecal/SamplePerFrame);
uint32_t FrameTicks = CPULoadFramecal;
uint8_t SampleCounter =0;
/* CPU LOAD **********/
uint16_t CPU_LOAD =0;
 /* Calculated dependent on system frequency, pre-scaler and SystimeTicks entered by user in msec*/
 uint32_t TimerCounts;
 uint8_t OS_InitState =NOT_INITIALIZED;
 uint8_t CurrentNumofTasks =0;
 
 uint8_t SystemRunnigFlag =0;
 uint8_t SystemIdleFlag  =0;
 /*************************************************************************************/
 uint32_t OS_SYSTICKCOUNTER =0;
 /***************************************Tasks array*************************************/
 TaskData_t TasksArray[MAX_ALLOWED_TASKS]={{0}};
 
 /***************************************Task info***************************************/
 
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: OS_ERROR_t
* Description: Initialize the OS
******************************************************************************************/

OS_ERROR_t OS_Init(void)
{
	if (OS_InitState==NOT_INITIALIZED)
	{
		EnableGlobalInterrupts();
		GptInit();
		if (OS_Configuration.SysTickChannel > 3)
		{
			return InvalidChannel;
		}
		/* Initialize the Timer Channel used as SysTick */
		gTimerUsedChannel = OS_Configuration.SysTickChannel;
		
		/* Initialize Sys tick counts */
		uint16_t Prescaler;
		Prescaler =strGpt_Channels[gTimerUsedChannel].u8_Prescaler;
		/* To maintain the Sys tick entered to be in msec */
		TimerCounts = ((float32_t)( SYS_CLOCK_FREQUENCY* (OS_Configuration.SystickValue) )) /( Prescaler*SecTomsec);
		/* assign CPU Load timer channel */
		CPULoadTimCh = OS_Configuration.CPULoadTimerCH;
		
		/* Update OS Initialization state */
		OS_InitState =INITIALIZED;
		return OS_ERROR_OK;
		
	}
	
	return OS_ERROR_OK;
	
	
}
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: CPU Sleep Mode
******************************************************************************************/


void CPU_Sleep(void)
{
	Gpt_StartTimer(CPULoadTimCh);
	CPUSleepFlag=1;
	while(CPUSleepFlag==1);
	
	
}
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: CPU Sleep Period Calculations
******************************************************************************************/
uint32_t timerCounts;
void CPU_SleepCal(void)
{
	
	/* stop cpu sleep timer */
	
	Gpt_ReturnCounterVal(CPULoadTimCh,&timerCounts);
	GptStop(CPULoadTimCh);
	/* calculate the time relative to this counts */
	uint16_t TimerPrecsaler =strGpt_Channels[CPULoadTimCh].u8_Prescaler;
	float32_t Time = timerCounts *((float32_t)TimerPrecsaler/SYS_CLOCK_FREQUENCY);
	
	CPUSleepTime += Time;
	
}
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: CPU Load calculation per sample and frame
******************************************************************************************/
uint32_t OLD_TICK;
void CPU_LoadCal(void)
{
	/* to avoid entering this function multiple times in the same systick*/
	if (OLD_TICK!=OS_SYSTICKCOUNTER)
	{
	
	/* if sample tick happened */
	if (OS_SYSTICKCOUNTER % SampleTicks == 0)
	{
		
			OLD_TICK= OS_SYSTICKCOUNTER;
			
			uint8_t CPULoadPerSample =( ((float)SampleTime - CPUSleepTime ) / (SampleTime) ) *100;
			CPUloadSamples[SampleCounter]=CPULoadPerSample;
			SampleCounter++;
			if (SampleCounter==SamplePerFrame)
			{
				SampleCounter=0;
			}
			/* reset time */
			CPUSleepTime =0;
		
	}
	if (OS_SYSTICKCOUNTER % FrameTicks ==0)
	{
		OLD_TICK= OS_SYSTICKCOUNTER;
		CPU_LOAD=0;
		uint8_t u8_counter=0;
		for (u8_counter=0;u8_counter<SamplePerFrame;u8_counter++)
		{
			CPU_LOAD +=CPUloadSamples[u8_counter];
		}
		/* CPU Average per frame*/
		CPU_LOAD = CPU_LOAD/SamplePerFrame;
	}
		
	}
}
/******************************************************************************************/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: OS_ERROR_t
* Description: this function is called after each sys tick
******************************************************************************************/
void OS_TickCallBack(void)
{
	/********test***********/
	DIO_PORTA_DATA ^=(1<<0);
	/**********************/
	if (CPUSleepFlag==1)
	{
		CPU_SleepCal();
		CPUSleepFlag=0;
	}
	
	
	uint8_t u8_counter ;
	/* increment system tick counter */
	OS_SYSTICKCOUNTER ++;
	
	/* Increment Tasks counters */
	for(u8_counter=0;u8_counter<MAX_ALLOWED_TASKS;u8_counter++)
	{
		/* Check valid Task */
		if (TasksArray[u8_counter].TaskFunction !=NULL_PTR )
		{
			if (TasksArray[u8_counter].TaskState !=TaskSuspended)
			{
				
				TasksArray[u8_counter].TaskCounter ++;
			}
		}
			
	}
	/* start the Timer again */
	GptStart_aSync(gTimerUsedChannel,TimerCounts,OS_TickCallBack);
}
/******************************************************************************************/
/*****************************************************************************************
* Parameters (in): TaskId , TaskFunction ,TaskPeriod , TaskPriority
* Parameters (out): None
* Return value: OS_ERROR_t
* Description: this function is used to create a new task
******************************************************************************************/
OS_ERROR_t OS_CreateTask(uint8_t *TaskId ,TaskFunction_t TaskFunction , uint32_t TaskPeriod , uint8_t TaskPriority  )
{
	/* Check Tasks Array is Full */
	if (CurrentNumofTasks == MAX_ALLOWED_TASKS)
	{
		return OS_ERRORExceedMaxTasks;
	}
	/* Check null pointer */
	if (TaskFunction == NULL_PTR)
	{
		return OS_InvalidPtr;
	}
	/* Check out of range priority */
	if (TaskPriority > MAX_PRIORITY_NUM)
	{
		return OS_WrongPriority ;
	}
	
	/* Check pre-reserved Task ID */
	uint8_t U8_Counter=0;
/*	for(U8_Counter=0;U8_Counter<MAX_ALLOWED_TASKS;U8_Counter++)
	{
		if (TaskId == TasksArray[U8_Counter].TaskID)
		{
			return OS_PreUsedTaskId ;
		}
	}*/
	
	/* Create the Task */
	for(U8_Counter=0;U8_Counter<MAX_ALLOWED_TASKS;U8_Counter++)
	{
		/* check on empty task Location function */
		if (TasksArray[U8_Counter].TaskFunction==NULL_PTR)
		{
			//TasksArray[U8_Counter].TaskID = TaskId;
			*TaskId = U8_Counter+1;
			TasksArray[U8_Counter].TaskID = U8_Counter+1;
			TasksArray[U8_Counter].periodicity=TaskPeriod;
			TasksArray[U8_Counter].priority =TaskPriority;
			TasksArray[U8_Counter].TaskFunction = TaskFunction;
			TasksArray[U8_Counter].TaskState  = TaskReady;
			TasksArray[U8_Counter].TaskCounter =0;
			
			/* Increment Num Of Tasks */
			CurrentNumofTasks++;
			
			return OS_TaskCreated;
		}
	}
	
	return OS_ERROR_OK ;
}
/*****************************************************************************************
* Parameters (in): TaskId 
* Parameters (out): None
* Return value: OS_ERROR_t
* Description: this function is used to create a new task
******************************************************************************************/
OS_ERROR_t OS_DeleteTask(uint8_t TaskId )
{
	uint8_t U8_Counter=0;
	for(U8_Counter=0;U8_Counter<MAX_ALLOWED_TASKS;U8_Counter++)
	{
		if (TaskId == TasksArray[U8_Counter].TaskID)
		{
			/* Reset Task Location */
			TasksArray[U8_Counter].periodicity=0;
			TasksArray[U8_Counter].TaskID=0;
			TasksArray[U8_Counter].TaskFunction =NULL_PTR;
			
			/* Decrement Number of Tasks */
			CurrentNumofTasks --;
			
			return OS_TaskDeleted ;
		}
	}
	return OS_NotExistTaskId;
}
/****************************************************************************************/

/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: this function is used to return the highest priority ready task
******************************************************************************************/

static taskId_t OS_CheckPriority(void)
{
	uint8_t u8_counter =0;
	uint8_t HighestPriority =MAX_PRIORITY_NUM; //Note high priority means smaller number
	taskId_t TaskID=0;
	/* Loop to get Highest Priority Ready Task */
	for(u8_counter=0;u8_counter<MAX_ALLOWED_TASKS;u8_counter++)
	{
		/* Check valid Task */
		if (TasksArray[u8_counter].TaskFunction !=NULL_PTR )
		{
			/* Check if it is a ready Task */
			if (TasksArray[u8_counter].TaskState == TaskReady)
			{
				/* Check Highest Priority */
				if (TasksArray[u8_counter].priority < HighestPriority )
				{
					HighestPriority = TasksArray[u8_counter].priority;
					TaskID = TasksArray[u8_counter].TaskID;
				}
			}
		}
	}
	return TaskID ;
}
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: this function is used to Calculate the periodicity and update the task state
******************************************************************************************/
static void OS_UpdateTaskState(void)
{
	uint8_t u8_counter =0;
	for(u8_counter=0;u8_counter<MAX_ALLOWED_TASKS;u8_counter++)
	{
		if (TasksArray[u8_counter].TaskFunction !=NULL_PTR)
		{
			if (TasksArray[u8_counter].TaskState !=TaskSuspended)
			{
				if (TasksArray[u8_counter].TaskCounter >= TasksArray[u8_counter].periodicity)
				{
					TasksArray[u8_counter].TaskState = TaskReady;
					/* Reset task  counter */
					TasksArray[u8_counter].TaskCounter =0;
				}
			}
			
		}
	}
}
/*******************************************************************************************/
/*****************************************************************************************
* Parameters (in): TaskId
* Parameters (out): None
* Return value: OS_ERROR_t
* Description: this function is used to Handle the highest priority ready task
******************************************************************************************/
static OS_ERROR_t OS_TaskHandler(taskId_t TaskId)
{
	uint8_t u8_counter;
	if (TaskId==0)
	{
		return OS_NotExistTaskId;
	}
	
	
	for (u8_counter=0;u8_counter<MAX_ALLOWED_TASKS;u8_counter++)
	{
		if (TasksArray[u8_counter].TaskID == TaskId)
		{
			TasksArray[u8_counter].TaskState= TaskRunning;
			/* Execute the task */
			TasksArray[u8_counter].TaskFunction();
			/* Update Task state */
			TasksArray[u8_counter].TaskState=TaskBlocked;
		}
	}
	
	return OS_ERROR_OK;
}
/*******************************************************************************************/
/*****************************************************************************************
* Parameters (in): None
* Parameters (out): None
* Return value: None
* Description: this function is the OS scheduler
******************************************************************************************/
uint8_t Taskid;
void OS_Run(void)
{
	OS_Init();
	/*set timer systick */
	GptStart_aSync(gTimerUsedChannel,TimerCounts,OS_TickCallBack);
	while(1)
	{
		CPU_LoadCal();
		OS_UpdateTaskState();
		Taskid =OS_CheckPriority();
		if (Taskid !=0)
		{
			OS_TaskHandler(Taskid);
		}
		else
		{
			CPU_Sleep();
			/*CPU Sleep */
		}
	}
	
	
	
}

/*****************************************************************************************
* Parameters (in): TaskId
* Parameters (out): None
* Return value: OS_ERROR_t
* Description: this function is used to suspend a task to be resumed later
******************************************************************************************/
OS_ERROR_t OS_TaskSuspend(taskId_t TaskId)
{
	uint8_t u8_counter =0;
	for(u8_counter=0;u8_counter<MAX_ALLOWED_TASKS;u8_counter++)
	{
		if (TasksArray[u8_counter].TaskFunction !=NULL_PTR)
		{
			if (TasksArray[u8_counter].TaskID == TaskId)
			{
				TasksArray[u8_counter].TaskState =TaskSuspended ;
				
				return OS_TSuspended;
			}
		}
	}
	return OS_NotExistTaskId;
}
/*******************************************************************************/
/*****************************************************************************************
* Parameters (in): TaskId
* Parameters (out): None
* Return value: OS_ERROR_t
* Description: this function is used to resume a suspended task
******************************************************************************************/
OS_ERROR_t OS_TaskResume(taskId_t TaskId)
{
	uint8_t u8_counter =0;
	for(u8_counter=0;u8_counter<MAX_ALLOWED_TASKS;u8_counter++)
	{
		if (TasksArray[u8_counter].TaskFunction !=NULL_PTR)
		{
			if (TasksArray[u8_counter].TaskID == TaskId)
			{
				TasksArray[u8_counter].TaskState =TaskBlocked ;
				TasksArray[u8_counter].TaskCounter = 0;
				return OS_TResumed;
			}
		}
	}
	return OS_NotExistTaskId ;
}
/****************************************************************************************/
