/*
 * button.h
 *
 *  Created on: Oct 26, 2025
 *      Author: ADMIN
 */
#include "main.h"
#ifndef INC_BUTTON_H_
#define INC_BUTTON_H_

#define NORMAL_STATE SET
#define PRESSED_STATE RESET
#define LONG_PRESSED_STATE 3
#define MAX_BUTTON 3
#define TimeOut 50
#define INIT 2

typedef struct {
	GPIO_TypeDef* port;
	uint16_t pin;
} Button_HW_Map_t;

static const Button_HW_Map_t button_map[MAX_BUTTON] = {
	{BUTTON_1_GPIO_Port, BUTTON_1_Pin},
	{BUTTON_2_GPIO_Port, BUTTON_2_Pin},
	{BUTTON_3_GPIO_Port, BUTTON_3_Pin}
};

typedef struct{
	int flag;
	int TimeOutForKeyPress;
	int KeyReg_0;
	int KeyReg_1;
	int KeyReg_2;
	int KeyReg_3;
	int status;
}Button;

extern Button ButtonPool[MAX_BUTTON];

void Button_init();
int isButtonPressed(int index);
void subKeyProcess();
void getKeyInput();

#endif /* INC_BUTTON_H_ */
