	/*
 * schedular.h
 *
 *  Created on: Nov 11, 2025
 *      Author: ADMIN
 */
#include "main.h"
#include "global.h"

#ifndef INC_SCHEDULAR_H_
#define INC_SCHEDULAR_H_

#define MAX_TASK 4
#define NO_TASK_ID 0

typedef struct{
	void (*ptask)(void);
	int Runmme;
	int Delay;
	int Period;
	int TaskID;
}Tasks;


void SCH_Init();
void SCH_Update_Tasks();
int SCH_Add_Tasks(void(*pFunction)(void), int DELAY, int PERIOD);
void SCH_Dispatch_Tasks();
void SCH_Delete_Tasks();
int Get_New_Task_ID();


#endif /* INC_SCHEDULAR_H_ */
