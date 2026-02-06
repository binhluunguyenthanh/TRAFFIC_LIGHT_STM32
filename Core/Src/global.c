/*
 * global.c
 *
 *  Created on: Oct 29, 2025
 *      Author: ADMIN
 */
#include "global.h"


void LEDBlinky() {
    HAL_GPIO_TogglePin(LED_BLINKY_GPIO_Port, LED_BLINKY_Pin);
    Settimer(TIMER_BLINKY, 1000);
}
void Ledblinky(){
	Settimer(TIMER_BLINKY, 1000);
}


