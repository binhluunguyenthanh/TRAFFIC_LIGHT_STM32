/*
 * mode_2.c
 *
 *  Created on: Oct 31, 2025
 *      Author: ADMIN
 */
#include "mode_manual.h"

int fsm_manual_status = 0;

void FSM_Mode_Manual_run() {

    switch (fsm_manual_status) {
        case NS_RED_WE_GREEN:
            NS_red_WE_green();
            if(isButtonPressed(1)) fsm_manual_status = NS_RED_WE_YELLOW;
            break;
        case NS_RED_WE_YELLOW:
            NS_red_WE_yellow();
            if(isButtonPressed(1)) fsm_manual_status = NS_GREEN_WE_RED;
            break;
        case NS_GREEN_WE_RED:
            NS_green_WE_red();
            if(isButtonPressed(1)) fsm_manual_status = NS_YELLOW_WE_RED;
            break;
        case NS_YELLOW_WE_RED:
            NS_yellow_WE_red();
            if(isButtonPressed(1)) fsm_manual_status = NS_RED_WE_GREEN;
            break;
        default:
        	if(isButtonPressed(1)) fsm_manual_status = NS_RED_WE_GREEN;
        	break;
    }
}

