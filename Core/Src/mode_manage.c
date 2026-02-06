/*
 * mode_manage.c
 *
 *  Created on: Oct 31, 2025
 *      Author: ADMIN
 */
#include "mode_manage.h"

int g_current_mode = MODE_NORMAL;


int g_timeRed_setting   = 7;
int g_timeAmber_setting = 2;
int g_timeGreen_setting = 5;
int g_temp_value = 0;
int fsm_modify_light_status = MODIFY_RED;


int led_cycle_index = 0;

const uint16_t redPins[4]   = {LED_RED_N_Pin, LED_RED_E_Pin, LED_RED_S_Pin, LED_RED_W_Pin};
const uint16_t amberPins[4] = {LED_YELLOW_N_Pin, LED_YELLOW_E_Pin, LED_YELLOW_S_Pin, LED_YELLOW_W_Pin};
const uint16_t greenPins[4] = {LED_GREEN_N_Pin, LED_GREEN_E_Pin, LED_GREEN_S_Pin, LED_GREEN_W_Pin};


void status_led_modify_generic(GPIO_TypeDef* GPIOx, const uint16_t pinsToCycle[4]) {
    if (IsTimerExpired(TIMER_MODIFY_LIGHT)) {
        led_off();
        led_cycle_index = (led_cycle_index + 1) % 4;

        HAL_GPIO_WritePin(GPIOx, pinsToCycle[led_cycle_index], GPIO_PIN_SET);

        Settimer(TIMER_MODIFY_LIGHT, 500);
    }
}

void FSM_Mode_Modify_run(){
    switch (fsm_modify_light_status){

    case MODIFY_RED:
        status_led_modify_generic(GPIOA, redPins);
        if (isButtonPressed(1)) {
            g_temp_value++;
            if (g_temp_value > 99) g_temp_value = 1;
        }
        if (isButtonPressed(2)) {
            g_timeRed_setting = g_temp_value;
        }
        if(isButtonPressed(0)){
            fsm_modify_light_status = MODIFY_YELLOW;
            g_temp_value = g_timeAmber_setting;
            led_cycle_index = 0;
            Settimer(TIMER_MODIFY_LIGHT, 10);
        }
        break;

    case MODIFY_YELLOW:
        status_led_modify_generic(GPIOA, amberPins);
        if (isButtonPressed(1)) {
            g_temp_value++;
            if (g_temp_value > 99) g_temp_value = 1;
        }
        if (isButtonPressed(2)) {
            g_timeAmber_setting = g_temp_value;
        }
        if(isButtonPressed(0)){
            fsm_modify_light_status = MODIFY_GREEN;
            g_temp_value = g_timeGreen_setting;
            led_cycle_index = 0;
            Settimer(TIMER_MODIFY_LIGHT, 10);
        }
        break;

    case MODIFY_GREEN:
        status_led_modify_generic(GPIOA, greenPins);
        if (isButtonPressed(1)) {
            g_temp_value++;
            if (g_temp_value > 99) g_temp_value = 1;
        }
        if (isButtonPressed(2)) {
            g_timeGreen_setting = g_temp_value;
        }
        if(isButtonPressed(0)){
            g_current_mode = MODE_NORMAL;
            Light_init();
        }
        break;

    default:
        fsm_modify_light_status = MODIFY_RED;
        g_temp_value = g_timeRed_setting;
        break;
    }

    uint8_t d1 = g_temp_value / 10;
    uint8_t d2 = g_temp_value % 10;
    uint8_t d3 = 0, d4 = 0;

    if (fsm_modify_light_status == MODIFY_RED) {
         d3 = g_timeRed_setting / 10;
         d4 = g_timeRed_setting % 10;
    } else if (fsm_modify_light_status == MODIFY_YELLOW) {
         d3 = g_timeAmber_setting / 10;
         d4 = g_timeAmber_setting % 10;
    } else if (fsm_modify_light_status == MODIFY_GREEN) {
         d3 = g_timeGreen_setting / 10;
         d4 = g_timeGreen_setting % 10;
    }
    update4Digits(d1, d2, d3, d4);
}


void FSM_Manager_run() {

    switch (g_current_mode) {

        case MODE_NORMAL:
            FSM_Mode_Normal_run();
            if (isButtonPressed(0)) {

                g_current_mode = MODE_MANUAL;

                fsm_modify_light_status = MODIFY_RED;
                g_temp_value = g_timeRed_setting;
                led_cycle_index = 0;
                led_off();
                Settimer(TIMER_MODIFY_LIGHT, 10);
            }
            break;
        case MODE_MANUAL:
        	FSM_Mode_Manual_run();
        	if (isButtonPressed(0)) {
        	    g_current_mode = MODE_MODIFY;
        	    fsm_manual_status = NS_RED_WE_GREEN;
        	}
            break;
        case MODE_MODIFY:
            FSM_Mode_Modify_run();
            break;

        default:
            g_current_mode = MODE_NORMAL;
            break;
    }
}

