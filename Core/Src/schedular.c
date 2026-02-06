/*
 * schedular.c
 *
 *  Created on: Nov 11, 2025
 *      Author: ADMIN
 */
#include "schedular.h"

static int newTaskId = 0;
static Tasks SCH_Tasks_G[MAX_TASK];

void SCH_Init(){
	Timer_init();
	Button_init();
	Light_init();
	Ledblinky();
}

void SCH_Update_Tasks(){
	if(SCH_Tasks_G[0].ptask && SCH_Tasks_G[0].Runmme == 0){
		if(SCH_Tasks_G[0].Delay > 0){
			SCH_Tasks_G[0].Delay--;
		}
		if(SCH_Tasks_G[0].Delay <= 0){
			SCH_Tasks_G[0].Runmme = 1;
		}
	}
}
int SCH_Add_Tasks(void(*pFunction)(), int DELAY, int PERIOD){
	int sumDelay = 0;
	int newDelay = 0;
	int newTaskId = 0;
	for(newTaskId = 0; newTaskId < MAX_TASK; newTaskId++){
		sumDelay += SCH_Tasks_G[newTaskId].Delay;
		if(sumDelay > DELAY){
			newDelay = DELAY - (sumDelay - SCH_Tasks_G[newTaskId].Delay);
			SCH_Tasks_G[newTaskId].Delay = sumDelay - DELAY;
			for(int i = MAX_TASK - 1; i > newTaskId; i--){
				SCH_Tasks_G[i].Delay = SCH_Tasks_G[i - 1].Delay;
				SCH_Tasks_G[i].Period = SCH_Tasks_G[i - 1].Period;
				SCH_Tasks_G[i].ptask = SCH_Tasks_G[i - 1].ptask;
				SCH_Tasks_G[i].TaskID = SCH_Tasks_G[i - 1].TaskID;
			}
			SCH_Tasks_G[newTaskId].Delay = newDelay;
			SCH_Tasks_G[newTaskId].Period = PERIOD;
			SCH_Tasks_G[newTaskId].ptask = pFunction;
				if(SCH_Tasks_G[newTaskId].Delay <= 0){
					SCH_Tasks_G[newTaskId].Runmme = 1;
				}
				else{
					SCH_Tasks_G[newTaskId].Runmme = 0;
				}
				SCH_Tasks_G[newTaskId].TaskID = Get_New_Task_ID();
				return SCH_Tasks_G[newTaskId].TaskID;
		}
		else{
			if(SCH_Tasks_G[newTaskId].ptask == 0){
				SCH_Tasks_G[newTaskId].Delay = DELAY - sumDelay;
				SCH_Tasks_G[newTaskId].Period = PERIOD;
				SCH_Tasks_G[newTaskId].ptask = pFunction;
				if(SCH_Tasks_G[newTaskId].Delay <= 0){
					SCH_Tasks_G[newTaskId].Runmme = 1;
				}
				else{
					SCH_Tasks_G[newTaskId].Runmme = 0;
				}
				SCH_Tasks_G[newTaskId].TaskID = Get_New_Task_ID();
				return SCH_Tasks_G[newTaskId].TaskID;
			}
		}
	}
	return SCH_Tasks_G[newTaskId].TaskID;
}
int SCH_Delete_Task(int taskID){
	int Return_code  = 0;
	int taskIndex = 0;
	int j;
	if(taskID != NO_TASK_ID){
		for(taskIndex = 0; taskIndex < MAX_TASK; taskIndex ++){
			if(SCH_Tasks_G[taskIndex].TaskID == taskID){
				Return_code = 1;
				if(taskIndex != 0 && taskIndex < MAX_TASK - 1){
					if(SCH_Tasks_G[taskIndex+1].ptask != 0){
						SCH_Tasks_G[taskIndex+1].Delay += SCH_Tasks_G[taskIndex].Delay;
					}
				}

				for( j = taskIndex; j < MAX_TASK - 1; j ++){
					SCH_Tasks_G[j].ptask = SCH_Tasks_G[j+1].ptask;
					SCH_Tasks_G[j].Period = SCH_Tasks_G[j+1].Period;
					SCH_Tasks_G[j].Delay = SCH_Tasks_G[j+1].Delay;
					SCH_Tasks_G[j].Runmme = SCH_Tasks_G[j+1].Runmme;
					SCH_Tasks_G[j].TaskID = SCH_Tasks_G[j+1].TaskID;
				}
				SCH_Tasks_G[j].ptask = 0;
				SCH_Tasks_G[j].Period = 0;
				SCH_Tasks_G[j].Delay = 0;
				SCH_Tasks_G[j].Runmme = 0;
				SCH_Tasks_G[j].TaskID = 0;
				return Return_code;
			}
		}
	}
	return Return_code;
}

void SCH_Dispatch_Tasks(void){
	if(SCH_Tasks_G[0].Runmme > 0) {
		(*SCH_Tasks_G[0].ptask)();
		SCH_Tasks_G[0].Runmme = 0;
		Tasks temtask = SCH_Tasks_G[0];
		SCH_Delete_Task(temtask.TaskID);
		if (temtask.Period != 0) {
			SCH_Add_Tasks(temtask.ptask, temtask.Period, temtask.Period);
		}
	}
}


int Get_New_Task_ID(void){
	newTaskId++;
	if(newTaskId == NO_TASK_ID){
		newTaskId++;
	}
	return newTaskId;
}

