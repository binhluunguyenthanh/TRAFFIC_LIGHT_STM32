/*
 * button.c
 *
 *  Created on: Oct 26, 2025
 *      Author: ADMIN
 */
#include "button.h"

Button ButtonPool[MAX_BUTTON];

void Button_init(){
	for(int i = 0; i < MAX_BUTTON; i++){
		ButtonPool[i].flag = 0;
		ButtonPool[i].TimeOutForKeyPress = TimeOut;
		ButtonPool[i].KeyReg_0 = NORMAL_STATE;
		ButtonPool[i].KeyReg_1 = NORMAL_STATE;
		ButtonPool[i].KeyReg_2 = NORMAL_STATE;
		ButtonPool[i].KeyReg_3 = NORMAL_STATE;
	}
}
int isButtonPressed(int index){
	if(ButtonPool[index].flag == 1){
		ButtonPool[index].flag = 0;
		return 1;
	}
	return 0;
}

void subKeyProcess(int index){
	ButtonPool[index].flag = 1;
}

void getKeyInput(){
	for (int i = 0; i < MAX_BUTTON; i++) {

		ButtonPool[i].KeyReg_0 = ButtonPool[i].KeyReg_1;
	    ButtonPool[i].KeyReg_1 = ButtonPool[i].KeyReg_2;
	    ButtonPool[i].KeyReg_2 = HAL_GPIO_ReadPin(button_map[i].port, button_map[i].pin);

	    if ((ButtonPool[i].KeyReg_0 == ButtonPool[i].KeyReg_1) && (ButtonPool[i].KeyReg_1 == ButtonPool[i].KeyReg_2)) {
	            ButtonPool[i].KeyReg_3 = ButtonPool[i].KeyReg_2;
	        } else {
	            continue;
	        }

	        switch (ButtonPool[i].status) {
	            case INIT:
	                ButtonPool[i].status = NORMAL_STATE;
	                break;
	            case NORMAL_STATE:
	                if (ButtonPool[i].KeyReg_3 == PRESSED_STATE) {
	                    subKeyProcess(i);
	                    ButtonPool[i].TimeOutForKeyPress = TimeOut;
	                    ButtonPool[i].status = PRESSED_STATE;
	                }
	                break;
	            case PRESSED_STATE:
	                if (ButtonPool[i].KeyReg_3 == NORMAL_STATE) {
	                    ButtonPool[i].status = NORMAL_STATE;
	                } else {
	                    ButtonPool[i].TimeOutForKeyPress--;
	                    if (ButtonPool[i].TimeOutForKeyPress == 0) {
	                        subKeyProcess(i);
	                        ButtonPool[i].TimeOutForKeyPress = TimeOut;
	                        ButtonPool[i].status = LONG_PRESSED_STATE;
	                    }
	                }
	                break;
	            case LONG_PRESSED_STATE:
	                if (ButtonPool[i].KeyReg_3 == NORMAL_STATE) {
	                    ButtonPool[i].status = NORMAL_STATE;
	                } else {
	                    ButtonPool[i].TimeOutForKeyPress--;
	                    if (ButtonPool[i].TimeOutForKeyPress == 0) {
	                        subKeyProcess(i);
	                        ButtonPool[i].TimeOutForKeyPress = TimeOut;
	                    }
	                }
	                break;
	        }
	  }
}

