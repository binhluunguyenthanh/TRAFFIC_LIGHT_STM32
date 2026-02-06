/*
 * mode_1.c
 *
 *  Created on: Oct 31, 2025
 *      Author: ADMIN
 */
#include "mode_normal.h"

int fsm_normal_status = INIT_LIGHT;
int g_timer_countdown_NS = 0;
int g_timer_countdown_WE = 0;

void Light_init(){
	fsm_normal_status = INIT_LIGHT;
	g_timer_countdown_NS = g_timeRed_setting;
	g_timer_countdown_WE = g_timeGreen_setting;
	Settimer(TIMER_COUNTDOWN_NS, 1000);
	Settimer(TIMER_COUNTDOWN_WE, 1000);
}


void FSM_Mode_Normal_run() {

    if (IsTimerExpired(TIMER_COUNTDOWN_NS)) {
        if (g_timer_countdown_NS > 0) g_timer_countdown_NS--;
        Settimer(TIMER_COUNTDOWN_NS, 1000);
    }
    if (IsTimerExpired(TIMER_COUNTDOWN_WE)) {
        if (g_timer_countdown_WE > 0) g_timer_countdown_WE--;
        Settimer(TIMER_COUNTDOWN_WE, 1000);
    }

    switch (fsm_normal_status) {
        case INIT_LIGHT:
            led_off();
            fsm_normal_status = NS_RED_WE_GREEN;
            Settimer(TIMER_FSM_NORMAL, g_timeGreen_setting * 1000);
            break;
        case NS_RED_WE_GREEN:
            NS_red_WE_green();
            if (IsTimerExpired(TIMER_FSM_NORMAL)) {
                fsm_normal_status = NS_RED_WE_YELLOW;
                g_timer_countdown_WE = g_timeAmber_setting;
                Settimer(TIMER_FSM_NORMAL, g_timeAmber_setting * 1000);
            }
            break;
        case NS_RED_WE_YELLOW:
            NS_red_WE_yellow();
            if (IsTimerExpired(TIMER_FSM_NORMAL)) {
                fsm_normal_status = NS_GREEN_WE_RED;
                g_timer_countdown_NS = g_timeGreen_setting;
                g_timer_countdown_WE = g_timeRed_setting;
                Settimer(TIMER_FSM_NORMAL, g_timeGreen_setting * 1000);
            }
            break;
        case NS_GREEN_WE_RED:
            NS_green_WE_red();
            if (IsTimerExpired(TIMER_FSM_NORMAL)) {
                fsm_normal_status = NS_YELLOW_WE_RED;
                g_timer_countdown_NS = g_timeAmber_setting;
                Settimer(TIMER_FSM_NORMAL, g_timeAmber_setting * 1000);
            }
            break;
        case NS_YELLOW_WE_RED:
            NS_yellow_WE_red();
             if (IsTimerExpired(TIMER_FSM_NORMAL)) {
                fsm_normal_status = NS_RED_WE_GREEN;
                g_timer_countdown_NS = g_timeRed_setting;
                g_timer_countdown_WE = g_timeGreen_setting;
                Settimer(TIMER_FSM_NORMAL, g_timeGreen_setting * 1000);
            }
            break;
    }

    uint8_t d1 = g_timer_countdown_NS / 10;
    uint8_t d2 = g_timer_countdown_NS % 10;
    uint8_t d3 = g_timer_countdown_WE / 10;
    uint8_t d4 = g_timer_countdown_WE % 10;
    update4Digits(d1, d2, d3, d4);
}
